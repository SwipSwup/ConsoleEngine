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

    Vector2D Window::GetDimensions()
    {
        return *windowDimensions;
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

    }

    void Window::Init(Vector2D size)
    {
        AllocConsole();
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if(hConsole == INVALID_HANDLE_VALUE)
        {
            //todo print error
            //todo close engine

            return;
        }



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

    void Window::PushRenderData(char*** data, Vector2D size, Vector2D origin)
    {
        for (int y = size.y; y > 0; --y)
        {
            int yIndex = windowDimensions->y - origin.y - y;

            if(yIndex < 0)
                break;

            if(yIndex > windowDimensions->y - 1)
                continue;

            for (int x = 0; x < size.x; ++x)
            {
                int xIndex = x + origin.x;

                if(xIndex > windowDimensions->x - 1)
                    break;

                if(xIndex < 0)
                    continue;

                renderBuffer[yIndex][xIndex] = data[y - 1][x];
            }
        }
    }
} // Engine
