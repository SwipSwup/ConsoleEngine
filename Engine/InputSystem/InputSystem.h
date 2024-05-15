//
// Created by david on 15/05/2024.
//

#ifndef CONSOLEENGINE_INPUTSYSTEM_H
#define CONSOLEENGINE_INPUTSYSTEM_H

#include <queue>

/*
 * ############ Resources ############
 * Keycodes: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */

namespace InputSystem
{

    class InputSystem
    {
    public:
        void Initialize();

        void Run();


    private:

    public:
        bool TryGetInputAction(wchar_t keyCode);
    };

} // InputSystem

#endif //CONSOLEENGINE_INPUTSYSTEM_H
