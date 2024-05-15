//
// Created by david on 15/05/2024.
//

#ifndef INPUTACTION_H
#define INPUTACTION_H

#include <vector>
#include <functional>
#include <string>
#include "KeyBind.h"

namespace Engine
{
    class InputSystem;

    class InputAction
    {
    public:
        InputAction(std::string identifier);


    private:
        std::string identifier;

        std::vector<KeyBind*> keyBinds;

    public:
        std::string GetIdentifier();

        void AddKeyBind(KeyBind* bind);

        void RemoveKeyBind(char bind);
    };

} // Engine

#endif //INPUTACTION_H
