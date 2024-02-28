//
// Created by david on 24/02/2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <bemapiset.h>

namespace Engine
{
    struct Sprite;
}

namespace Engine
{
    class Vector2D;
}

namespace Engine
{
    class Window
    {
    public:
        Window(Vector2D dimensions, bool bDrawBoarder);
        virtual ~Window();

        Vector2D GetDimensions();

    private:
        bool bDrawBorder;
        Vector2D* windowDimensions;

        HANDLE hConsole;

    public:
        void Render();

        void ClearRenderBuffer();

        void PushRenderData(char*** data, Vector2D size, Vector2D origin);

    private:
        void Init(Vector2D size);

        void InitRenderBuffer();
        char*** renderBuffer;

    };
} // Engine

#endif //WINDOW_H
