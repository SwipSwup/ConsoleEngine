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

/*
 * ############ Resources ############
 * Keycodes: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */

namespace Engine
{
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


    private:
        std::vector<InputAction*> inputActions;

        std::unordered_map<int, std::vector<InputAction*>> registeredInputActions;

        std::queue<int> keyBoardEvents;

        HANDLE window;

    public:
        void AddInputAction(InputAction* action);

        void ConsumeKeyBoardEvents();

        InputAction* FindInputAction(const std::string& identifier);
    };

} // Engine

#endif //INPUTSYSTEM_H
