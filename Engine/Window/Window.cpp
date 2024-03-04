//
// Created by david on 24/02/2024.
//

#include "Window.h"

#include <iostream>
#include <windows.h>

#include "../Utility/Vector2D.h"
#include "../Utility/Color.h"
#include "../Utility/Sprites/Sprite.h"

namespace Engine
{
    RenderObject::RenderObject() : color(Color::WHT)
    {
        data = ' ';
    }

    RenderObject::RenderObject(wchar_t data, Color color): color(color)
    {
        this->data = data;
    }

    Window::Window(SHORT x, SHORT y, bool bDrawBorder)
    {
        this->windowSize = COORD{x, y};

        this->bDrawBorder = bDrawBorder;

        bHighlightUnchangedPositions = false;

        Init();
    }

    Window::~Window()
    {
        delete cursorInfo;
        delete[] renderBuffer;
        delete[] previousRenderBuffer;
        delete[] zBufferIndex;
    }

    int Window::TranslateToBufferIndex(int x, int y, int xDimension)
    {
        return x + y * xDimension;
    }

    bool Window::HasRenderObjectUpdated(int xy)
    {
        return previousRenderBuffer[xy].data == renderBuffer[xy].data &&
            !strcmp(previousRenderBuffer[xy].color.escapeCode, renderBuffer[xy].color.escapeCode);
    }

    void Window::Render()
    {
        DWORD charsWritten;

        for (int y = 0; y < windowSize.Y; ++y)
        {
            for (int x = 0; x < windowSize.X; ++x)
            {
                int bufferIndex = TranslateToBufferIndex(x, y, windowSize.X);
                RenderObject obj = renderBuffer[bufferIndex];

                Color c = obj.color;

                if (HasRenderObjectUpdated(bufferIndex))
                {
                    if (bHighlightUnchangedPositions)
                    {
                        c = Color::GRNHB;
                    }
                    else
                    {
                        continue;
                    }
                }

                SetConsoleCursorPosition(hConsole, COORD{(SHORT)x, (SHORT)y});
                if (!WriteConsoleA(
                    hConsole,
                    c.escapeCode,
                    c.escapeCodeLength,
                    &charsWritten,
                    nullptr
                ) || !WriteConsoleW(
                    hConsole,
                    &obj.data,
                    1,
                    &charsWritten,
                    nullptr
                ))
                {
                    std::cerr << "Error writing to console" << std::endl;
                    return;
                }
            }
        }

        ConsumeRenderBuffer();
    }

    void Window::UpdateConsoleMode(DWORD mode, bool bEnable)
    {
        if (bEnable)
        {
            dwMode |= mode;
        }
        else
        {
            dwMode &= ~mode;
        }

        if (!SetConsoleMode(hConsole, dwMode))
        {
            std::cerr << "Error setting console mode" << std::endl;
        }
    }

    void Window::HighlightUnchangedPositions(bool bHighlight)
    {
        bHighlightUnchangedPositions = bHighlight;
    }

    int Window::GetWindowXDimension()
    {
        return windowSize.X;
    }

    int Window::GetWindowYDimension()
    {
        return windowSize.Y;
    }

    void Window::Init()
    {
        AllocConsole();
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if (hConsole == INVALID_HANDLE_VALUE)
        {
            //todo print error
            //todo close engine

            return;
        }

        hwConsole = GetConsoleWindow();

        fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        if (!GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo))
        {
            std::cerr << "Error getting current console font" << std::endl;
            return;
        }

        RECT rect;
        GetWindowRect(hwConsole, &rect);
        //todo
        MoveWindow(hwConsole, rect.left, rect.top, fontInfo.dwFontSize.X * windowSize.X + 33,
                   fontInfo.dwFontSize.Y * windowSize.Y + 39, TRUE);

        if (!GetConsoleMode(hConsole, &dwMode))
        {
            std::cerr << "Error getting console mode" << std::endl;
            return;
        }
        UpdateConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING, true);

        InitCursor();

        InitRenderBuffer();
    }

    void Window::InitCursor()
    {
        cursorInfo = new CONSOLE_CURSOR_INFO;
        cursorInfo->bVisible = FALSE;
        cursorInfo->dwSize = 1;

        if (!SetConsoleCursorInfo(hConsole, cursorInfo))
        {
            std::cerr << "Error setting console cursor info" << std::endl;
        }
    }

    void Window::InitRenderBuffer()
    {
        previousRenderBuffer = new RenderObject[windowSize.X * windowSize.Y];
        renderBuffer = new RenderObject[windowSize.X * windowSize.Y];
        zBufferIndex = new int[windowSize.X * windowSize.Y];

        for (int i = 0; i < windowSize.X * windowSize.Y; ++i)
        {
            zBufferIndex[i] = 0;
        }
    }

    void Window::ConsumeRenderBuffer()
    {
        memcpy(previousRenderBuffer, renderBuffer, sizeof(RenderObject) * windowSize.X * windowSize.Y);

        delete renderBuffer;
        renderBuffer = new RenderObject[windowSize.X * windowSize.Y];

        for (int i = 0; i < windowSize.X * windowSize.Y; ++i)
        {
            zBufferIndex[i] = -1;
        }
    }

    void Window::WriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color)
    {
        if (zBufferIndex[xy] > z || xy < 0 || xy > windowSize.X * windowSize.Y - 1)
        {
            return;
        }

        ForceWriteRawIntoRenderBuffer(xy, z, data, color);
    }

    void Window::ForceWriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color)
    {
        renderBuffer[xy] = RenderObject{data, color};

        zBufferIndex[xy] = z;
    }


    void Window::WDrawSprite(Sprite* sprite, int originX, int originY, int z)
    {
        //todo might be able to be done in just one loop
        //todo fix if x is bigger than x dimension that it doesnt loop back one y lower
        for (int y = 0; y < sprite->textureDimensions->y; ++y)
        {
            for (int x = 0; x < sprite->textureDimensions->x; ++x)
            {
                WriteRawIntoRenderBuffer(
                    TranslateToBufferIndex(
                        x + originX,
                        windowSize.Y - originY - sprite->textureDimensions->y + y,
                        windowSize.X
                    ),
                    z,
                    sprite->texture[y][x],
                    sprite->color[y][x]
                );
            }
        }
    }

    void Window::WDrawText(const char* text, int originX, int originY, int z)
    {
        WDrawText(text, Color::WHT, originX, originY, z);
    }

    void Window::WDrawText(const char* text, Color color, int originX, int originY, int z)
    {
        for (int x = 0; x < strlen(text); ++x)
        {
            WriteRawIntoRenderBuffer(
                TranslateToBufferIndex(
                    x + originX,
                    windowSize.Y - originY - 1,
                    windowSize.X
                ),
                z,
                text[x],
                color
            );
        }
    }
} // Engine
