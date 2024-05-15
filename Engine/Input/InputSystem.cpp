//
// Created by david on 21/04/2024.
//

#include "InputSystem.h"

namespace Engine
{
    void InputSystem::Initialize()
    {

    }

    void InputSystem::Run()
    {
        if (hStdin == INVALID_HANDLE_VALUE) {
            std::cerr << "Error: Unable to retrieve standard input handle\n";
            return 1;
        }

        while (true) {
            if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
                std::cerr << "Error reading input events\n";
                break;
            }

            for (DWORD i = 0; i < cNumRead; i++) {
                if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                    // Handle key events
                    wchar_t ch = irInBuf[i].Event.KeyEvent.uChar.UnicodeChar;
                    std::wcout << L"Pressed key: " << ch << std::endl;
                }
            }
        }
    }
} // Engine