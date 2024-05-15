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
        void AddListener(std::function<void>);
    private:
        wchar_t key;

        std::vector<std::function<void>> listeners;
    };

} // InputSystem

#endif //CONSOLEENGINE_INPUTACTION_H
