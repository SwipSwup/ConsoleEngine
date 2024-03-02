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
        bool bHighlightUnchangedPositions;
        COORD windowSize;

        HANDLE hConsole;
        CONSOLE_CURSOR_INFO* cursorInfo;
        DWORD dwMode;

        void Init();

        void InitCursor();

        int TranslateToBufferIndex(int x, int y, int xDimension);

        bool HasRenderObjectUpdated(int xy);

    public:
        void Render();

        void UpdateConsoleMode(DWORD mode, bool bEnable);

        void HighlightUnchangedPositions(bool bHighlight);

        int GetWindowXDimension();

        int GetWindowYDimension();

    private:
        RenderObject* previousRenderBuffer;
        RenderObject* renderBuffer;
        int* zBufferIndex;

        void ConsumeRenderBuffer();

        void InitRenderBuffer();

        void WriteRawIntoRenderBuffer(int xy, int z, char data, Color color);

        void ForceWriteRawIntoRenderBuffer(int xy, int z, char data, Color color);

    public:
        void WDrawSprite(Sprite* sprite, int originX, int originY, int z);

        void WDrawText(const char* text, int originX, int originY, int z);

        void WDrawText(const char* text, Color color, int originX, int originY, int z);
    };
} // Engine

#endif //WINDOW_H
