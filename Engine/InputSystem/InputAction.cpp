//
// Created by david on 15/05/2024.
//

#include "InputAction.h"

namespace Engine
{
    std::string InputAction::GetIdentifier()
    {
        return identifier;
    }

    InputAction::InputAction(std::string identifier)
    {
        this->identifier = identifier;
    }

    void InputAction::AddKeyBind(KeyBind* bind)
    {
        keyBinds.push_back(bind);
    }

    void InputAction::RemoveKeyBind(char bind)
    {
        for (int i = 0; i < keyBinds.size(); ++i)
        {
            if(keyBinds[i]->keyChar == bind) {
                delete keyBinds[i];
                keyBinds.erase(keyBinds.begin() + i);
                return;
            }
        }
    }
} // Engine