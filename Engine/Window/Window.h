//
// Created by david on 24/02/2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <windows.h>
#include "../Utility/Color.h"

namespace Engine
{
    struct Sprite;

    struct RenderObject
    {
        RenderObject();
        RenderObject(char data, Color color);

        char data;
        Color color;
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

        int twoToOneDIndex(int x, int y, int xDimension);
    public:
        void Render();

        void UpdateConsoleMode(DWORD mode, bool enable);

        void PushSprite(int originX, int originY, int z, Sprite* sprite);

        //[][][][]
        //[][][][]
        //[][][][]
        //x + y * windowSize.Y
        //[][][][][][]
    private:
        RenderObject* previousRenderBuffer;
        RenderObject* renderBuffer;
        int* zBufferIndex;

        void ConsumeRenderBuffer();

        void InitRenderBuffer();

        void WriteRawIntoRenderBuffer(int xy, int z, char data, Color color);

        void ForceWriteRawIntoRenderBuffer(int xy, int z, char data, Color color);
    };
} // Engine

#endif //WINDOW_H
