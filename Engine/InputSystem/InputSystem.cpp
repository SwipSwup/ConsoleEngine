//
// Created by david on 15/05/2024.
//

#include <windows.h>
#include <winuser.h>
#include <iostream>
#include "InputSystem.h"
#include "../ConsoleEngine.h"

namespace Engine
{
    void InputSystem::Run()
    {
        while (1)
        {

            // Check if the 'A' key is currently pressed
            if (GetAsyncKeyState('A') & 0x8000) {
                std::cout << "'A' key is pressed." << std::endl;
            } else {
                std::cout << "'A' key is not pressed." << std::endl;
            }
            Sleep(100);

        }

        /*while (true) {
            // Check if the console window is the foreground window
            if (GetForegroundWindow() == consoleWindow) {
                // Check for keyboard input
                for (int i = 0; i < 256; ++i) {
                    short keyState = GetAsyncKeyState(i);
                    if (keyState & 0x8000) {
                        // Key is pressed
                        eventQueue.push({ i, true });
                    }
                    else if (keyState & 0x1) {
                        // Key was released
                        eventQueue.push({ i, false });
                    }
                }
            }

            // Process input events
            while (!eventQueue.empty()) {
                InputEvent event = eventQueue.front();
                eventQueue.pop();

                if (event.isKeyDown) {
                    std::cout << "Key " << static_cast<char>(event.keyCode) << " is pressed" << std::endl;
                }
                else {
                    std::cout << "Key " << static_cast<char>(event.keyCode) << " is released" << std::endl;
                }
            }

            // Add a short delay to reduce CPU usage
            Sleep(100);
        }*/
    }


    InputAction* InputSystem::FindInputAction(const std::string &identifier)
    {
        for (InputAction* item: inputActions)
        {
            if (item->GetIdentifier() == identifier)
                return item;
        }

        return nullptr;
    }

    InputSystem::~InputSystem()
    {
        // free all input actions
        for (const InputAction* item: inputActions)
        {
            delete item;
        }
    }

    void InputSystem::ConsumeKeyBoardEvents()
    {
        for (int i = 0; !keyBoardEvents.empty() && i < ConsoleEngine::settings->maxInputActionsPerFrame; ++i)
        {
            auto inputAction = registeredInputActions.find(keyBoardEvents.front());

            keyBoardEvents.pop();
        }
    }

    void InputSystem::AddInputAction(InputAction* action)
    {

    }

    InputSystem::InputSystem()
    {

    }
} // Engine