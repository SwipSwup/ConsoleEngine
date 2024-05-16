//
// Created by david on 15/05/2024.
//

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <queue>
#include <string>
#include <map>
#include <ntdef.h>
#include "InputAction.h"
#include "mutex"

/*
 * ############ Resources ############
 * Keycodes: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */

namespace Engine
{
    struct KeyEvent
    {
        WPARAM wParam;
        DWORD vkCode;
    };

    class InputSystem
    {
    public:
        InputSystem();

        InputSystem(HANDLE window)
        {
            this->window = window;
        }

        virtual ~InputSystem();

        void Run();

        void Stop();


    private:
        std::vector<InputAction*> inputActions;

        std::unordered_map<int, std::vector<InputAction*>> registeredInputActions;


        static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

        HHOOK hHook;

        HANDLE window;

    public:
        void AddInputAction(InputAction* action);

        void ConsumeKeyBoardEvents();

        InputAction* FindInputAction(const std::string &identifier);

    private:
        static std::mutex keyboardEventsMutex;

        static std::queue<KeyEvent> keyboardEvents;

        void ProcessInputEvents();
    };

} // Engine

#endif //INPUTSYSTEM_H
