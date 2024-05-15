//
// Created by david on 15/05/2024.
//

#ifndef CONSOLEENGINE_INPUTACTION_H
#define CONSOLEENGINE_INPUTACTION_H

#include <vector>
#include <functional>

namespace InputSystem
{
    enum KeyEvent {
        KEY_UP,
        KEY_DOWN
    };

    class InputAction
    {
    public:
        InputAction(int keyCode);
    private:
        int keyCode;
    };

} // InputSystem

#endif //CONSOLEENGINE_INPUTACTION_H
