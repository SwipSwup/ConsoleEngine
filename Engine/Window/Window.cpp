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

    RenderObject::RenderObject(char data, Color color): color(color)
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
    }

    int Window::TranslateToBufferIndex(int x, int y, int xDimension)
    {
        //return (x + windowSize.X / 2) + y * xDimension;
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

        //todo propably possible with just one loop
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

                //std::cout << "a";twoToOneDIndex(x, y, windowSize.X)
                SetConsoleCursorPosition(hConsole, COORD{(SHORT)x, (SHORT)y});
                //std::cout << obj.color.escapeCode << obj.data;
                if (!WriteConsoleA(
                        hConsole,
                        c.escapeCode,
                        c.escapeCodeLength,
                        &charsWritten,
                        nullptr
                    ) || !WriteConsoleA(
                        hConsole,
                        &obj.data,
                        1,
                        &charsWritten,
                        nullptr
                    ) ||
                    !WriteConsoleA(
                        hConsole,
                        Color::CRESET.escapeCode,
                        Color::CRESET.escapeCodeLength,
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




        // Set the size of the screen buffer
        /*if (!SetConsoleScreenBufferSize(hConsole, windowSize)) {
            std::cerr << "Error setting console screen buffer size" << std::endl;
            return;
        }*/
        // Define the size of the console window

        // Set the size of the console window

        CONSOLE_FONT_INFOEX fontInfo;
        fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

        if (!GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
            std::cerr << "Error getting current console font" << std::endl;
            return;
        }

        // Retrieve the font size
        DWORD fontIndex = fontInfo.nFont;
        COORD fontSize = GetConsoleFontSize(hConsole, fontIndex);

        // Define the desired number of characters for width and height
        int desiredWidthInChars = 80; // Change this value as needed
        int desiredHeightInChars = 24; // Change this value as needed

        // Calculate the desired console window size based on font size and character dimensions
        COORD desiredSize;
        std::cout << fontInfo.dwFontSize.X;

        desiredSize.X = fontInfo.dwFontSize.X * windowSize.X + 33;
        desiredSize.Y = fontInfo.dwFontSize.Y * windowSize.Y + 39;

        // Set the console window size
        if (!SetConsoleScreenBufferSize(hConsole, desiredSize)) {
            std::cerr << "Error setting console screen buffer size" << std::endl;
            return;
        }
        HWND console = GetConsoleWindow();
        RECT rect;
        GetWindowRect(console, &rect);

        MoveWindow(console, rect.left, rect.top, desiredSize.X, desiredSize.Y, TRUE);

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

    void Window::ConsumeRenderBuffer()
    {
        memcpy(previousRenderBuffer, renderBuffer, sizeof(RenderObject) * windowSize.X * windowSize.Y);

        delete renderBuffer;
        renderBuffer = new RenderObject[windowSize.X * windowSize.Y];

        for (int i = 0; i < windowSize.X * windowSize.Y; ++i)
        {
            zBufferIndex[i] = 0;
        }
    }

    void Window::WriteRawIntoRenderBuffer(int xy, int z, char data, Color color)
    {
        if (zBufferIndex[xy] > z || xy < 0 || xy > windowSize.X * windowSize.Y - 1)
        {
            return;
        }
        ForceWriteRawIntoRenderBuffer(xy, z, data, color);
    }

    void Window::ForceWriteRawIntoRenderBuffer(int xy, int z, char data, Color color)
    {
        renderBuffer[xy] = RenderObject{data, color};

        zBufferIndex[xy] = z;
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
