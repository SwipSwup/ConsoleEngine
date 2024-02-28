//
// Created by david on 24/02/2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <list>
#include <windows.h>

namespace Engine
{
    struct RenderCall {
        COORD position;
        COORD dataDimensions;
        char*** data;
    };

    class Window
    {
    public:
        Window(SHORT x, SHORT y, bool bDrawBoarder);
        virtual ~Window();

    private:
        bool bDrawBorder;
        COORD windowSize;

        HANDLE hConsole;
        CONSOLE_CURSOR_INFO* cursorInfo;
        DWORD dwMode;

        void Init();

        void InitCursor();

    public:
        void Render();

        void UpdateConsoleMode(DWORD mode, bool enable);

        void PushRenderCall(RenderCall call);

    private:
        std::list<RenderCall> renderBufferOld;

        char*** previousRenderBuffer;
        char*** renderBuffer;
        int** zBufferIndex;

        void ConsumeRenderBuffer();

        void InitRenderBuffer();

        void ClearConsole();

    };
} // Engine

#endif //WINDOW_H
