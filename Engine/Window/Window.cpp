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

        Init();
    }

    Window::~Window()
    {
        delete cursorInfo;
    }

    int Window::twoToOneDIndex(int x, int y, int xDimension)
    {
        return x + y * xDimension;
    }

    //TODO implement Z value
    //TODO implement buffer that gets initalized with " " and then adds the render calls so its possible to reduce the flicker
    void Window::Render()
    {
        DWORD charsWritten;

        for (int y = 0; y < windowSize.Y; ++y)
        {
            for (int x = 0; x < windowSize.X; ++x)
            {
                RenderObject obj = renderBuffer[twoToOneDIndex(x, y, windowSize.X)];

                Color c = obj.color;
                if (previousRenderBuffer[twoToOneDIndex(x, y, windowSize.X)].data == renderBuffer[
                    twoToOneDIndex(x, y, windowSize.X)].data && !strcmp(
                    previousRenderBuffer[twoToOneDIndex(x, y, windowSize.X)].color.escapeCode,
                    renderBuffer[twoToOneDIndex(x, y, windowSize.X)].color.escapeCode))
                {
                    //c = Color::WHT;
                    continue;
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

                /*if (!WriteConsoleA(
                    hConsole,
                    &obj.data,
                    1,
                    &charsWritten,
                    nullptr
                ))
                {
                    std::cerr << "Error writing to console" << std::endl;
                    return;
                }*/
            }
        }

        ConsumeRenderBuffer();
    }

    void Window::UpdateConsoleMode(DWORD mode, bool enable)
    {
        if (enable)
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

    void Window::PushSprite(int originX, int originY, int z, Sprite* sprite)
    {
        COORD bufferIndex;
        for (int y = 0; y < sprite->textureDimensions->y; ++y)
        {
            bufferIndex.Y = windowSize.Y - originY - sprite->textureDimensions->y + y;

            if (bufferIndex.Y > windowSize.Y - 1)
                break;

            if (bufferIndex.Y < 0)
                continue;

            for (int x = 0; x < sprite->textureDimensions->x; ++x)
            {
                bufferIndex.X = x + originX;

                if (bufferIndex.X > windowSize.X - 1)
                    break;

                if (bufferIndex.X < 0)
                    continue;

                //std::cout << sprite->texture[y][x];

                //std::cout << "x: " <<bufferIndex.X << " y: " << bufferIndex.Y << " index:" << twoToOneDIndex(bufferIndex.X, bufferIndex.Y, windowSize.X) << std::endl;

                WriteRawIntoRenderBuffer(twoToOneDIndex(bufferIndex.X, bufferIndex.Y, windowSize.X), z,
                                         sprite->texture[y][x],
                                         sprite->color[y][x]);
            }
        }
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


         InitCursor();

        // Set text color to red
        //SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

        // Enable ANSI escape code support
        dwMode = 0;

        if (!GetConsoleMode(hConsole, &dwMode))
        {
            std::cerr << "Error getting console mode" << std::endl;
            return;
        }
        UpdateConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING, true);

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
    }

    void Window::WriteRawIntoRenderBuffer(int xy, int z, char data, Color color)
    {
        if (previousRenderBuffer[xy].data == data &&
            !strcmp(previousRenderBuffer[xy].color.escapeCode, color.escapeCode) ||
            zBufferIndex[xy] > z)
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
} // Engine
