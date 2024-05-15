//
// Created by david on 15/05/2024.
//

#ifndef CONSOLEENGINE_KEYBIND_H
#define CONSOLEENGINE_KEYBIND_H

#include <string>

namespace Engine
{
    struct KeyBind
    {
    public:
        char keyChar;

        int GetKeyCode();

    private:
        int keyCode;
    };

} // Engine

#endif //CONSOLEENGINE_KEYBIND_H
