//
// Created by david on 24/02/2024.
//

#include "Window.h"

#include <iostream>
#include <windows.h>

namespace Engine
{
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

    //TODO implement Z value
    //TODO implement buffer that gets initalized with " " and then adds the render calls so its possible to reduce the flicker
    void Window::Render()
    {
        ClearConsole();

        DWORD charsWritten;
        COORD Index;

        for (RenderCall call : renderBufferOld)
        {
            for (int y = call.dataDimensions.Y; y > 0; --y)
            {
                Index.Y = windowSize.Y - call.position.Y - y;

                if (Index.Y < 0)
                    break;

                if (Index.Y > windowSize.Y - 1)
                    continue;

                for (int x = 0; x < call.dataDimensions.X; ++x)
                {
                    Index.X = x + call.position.X;

                    if (Index.X > windowSize.X - 1)
                        break;

                    if (Index.X < 0)
                        continue;

                    SetConsoleCursorPosition(hConsole, Index);

                    if (!WriteConsoleA(hConsole, call.data[call.dataDimensions.Y - y][x],
                                       strlen(call.data[call.dataDimensions.Y - y][x]), &charsWritten, nullptr))
                    {
                        std::cerr << "Error writing to console" << std::endl;
                        return;
                    }
                }
            }
        }
        renderBufferOld.clear();

        //ConsumeRenderBuffer();

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
        if (!GetConsoleMode(hConsole, &dwMode))
        {
            std::cerr << "Error getting console mode" << std::endl;
            return;
        }
        UpdateConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING, true);
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
        //renderBufferOld.clear();

        for (int y = 0; y < windowSize.Y; ++y)
        {
            for (int x = 0; x < windowSize.X; ++x)
            {
                renderBuffer[y][x] = (char*)" ";
            }
        }
    }

    void Window::InitRenderBuffer()
    {

    }

    void Window::ClearConsole()
    {
        DWORD charsWritten;
        for (short y = 0; y < windowSize.Y; ++y)
        {
            for (short x = 0; x < windowSize.X; ++x)
            {
                if (!WriteConsoleOutputCharacterA(hConsole, " ", 2, COORD{x, y}, &charsWritten)) {
                    std::cerr << "Error writing to console" << std::endl;
                    return;
                }
            }
        }
    }

    void Window::PushRenderCall(RenderCall call)
    {
        renderBufferOld.push_back(call);
    }
} // Engine
