//
// Created by david on 24/02/2024.
//

#include "Window.h"

#include <iostream>
#include <windows.h>

#include "../Utility/Sprite.h"
#include "../Utility/Vector2D.h"

namespace Engine
{
    Window::Window(Vector2D dimensions, bool bDrawBorder)
    {
        this->windowDimensions = new Vector2D(dimensions.x, dimensions.y);
        this->bDrawBorder = bDrawBorder;

        Init(dimensions);
    }

    Window::~Window()
    {
        delete windowDimensions;
    }

    void DrawHorizontalBorder(int windowWidth)
    {
        std::cout << "+";
        for (int i = 0; i < windowWidth; ++i)
        {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
    }

    void Window::Render()
    {
        if (bDrawBorder)
            DrawHorizontalBorder(windowDimensions->x);

        for (int y = 0; y < windowDimensions->y; ++y)
        {
            if (bDrawBorder)
                std::cout << "|";

            for (int x = 0; x < windowDimensions->x; ++x)
            {
                std::cout << renderBuffer[y][x];
            }

            if (bDrawBorder)
                std::cout << "|";
            std::cout << std::endl;
        }

        if (bDrawBorder)
            DrawHorizontalBorder(windowDimensions->x);
    }

    void Window::Init(Vector2D size)
    {
        InitRenderBuffer();

        HWND console = GetConsoleWindow();
        RECT rect;
        GetWindowRect(console, &rect);

        // Set the size of the console window
        // todo fix
        MoveWindow(console, rect.left, rect.top, 1000, 1000, TRUE);
    }

    void Window::InitRenderBuffer()
    {
        renderBuffer = new char**[windowDimensions->y];
        for (int i = 0; i < windowDimensions->y; ++i)
        {
            renderBuffer[i] = new char*[windowDimensions->x];
        }

        ClearRenderBuffer();
    }

    void Window::ClearRenderBuffer()
    {
        for (int y = 0; y < windowDimensions->y; ++y)
        {
            for (int x = 0; x < windowDimensions->x; ++x)
            {
                renderBuffer[y][x] = (char*)" ";
            }
        }
    }

    void Window::PushSpriteIntoRenderBuffer(Sprite* sprite, Vector2D origin)
    {
        for (int y = origin.y; y < origin.y + sprite->size->y; ++y)
        {
            for (int x = origin.x; x < origin.x + sprite->size->x; ++x)
            {
                renderBuffer[y][x] = sprite->GetTextureAndColorData(x, y);
            }
        }
    }
} // Engine
