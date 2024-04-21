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
        RenderObject(wchar_t data, Color color);

        wchar_t data;
        Color color;
    };

    class Window
    {
    public:
        Window(SHORT x, SHORT y);
        virtual ~Window();

    private:
        bool bHighlightUnchangedPositions;

        HANDLE hConsole{};
        HWND hwConsole{};
        COORD windowSize{};
        DWORD dwMode{};
        CONSOLE_CURSOR_INFO* cursorInfo{};
        CONSOLE_FONT_INFOEX fontInfo{};

        void Init();

        void InitCursor();

        int TranslateToBufferIndex(int x, int y, int xDimension);

        bool HasRenderObjectUpdated(int xy);

    public:
        void Render();

        void UpdateConsoleTitle(const char* title);

        void UpdateConsoleMode(DWORD mode, bool bEnable);

        void ShowRenderUpdates(bool bHighlight);

        int GetWindowXDimension();

        int GetWindowYDimension();

    private:
        RenderObject* previousRenderBuffer{};
        RenderObject* renderBuffer{};
        int* zBufferIndex{};

        void InitRenderBuffer();

        void ConsumeRenderBuffer();

        void WriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color);

        void ForceWriteRawIntoRenderBuffer(int xy, int z, wchar_t data, Color color);

    public:
        void WDrawSprite(Sprite* sprite, int originX, int originY, int z);

        void WDrawText(const char* text, int originX, int originY, int z);

        void WDrawText(const char* text, Color color, int originX, int originY, int z);
    };
} // Engine

#endif //WINDOW_H
