//
// Created by david on 15/05/2024.
//

#include "InputSystem.h"

namespace InputSystem
{
    void InputSystem::Run()
    {
        while (true) {
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
        }
    }
} // InputSystem