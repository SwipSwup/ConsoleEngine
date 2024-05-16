#include <windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "InputSystem.h"

namespace Engine
{
    bool bInputProcessingThreadActive = true;

    std::queue<KeyEvent> InputSystem::keyboardEvents;
    std::mutex InputSystem::keyboardEventsMutex;

    LRESULT CALLBACK InputSystem::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        if (nCode >= 0)
        {
            if (wParam == WM_KEYDOWN || wParam == WM_KEYUP)
            {
                KBDLLHOOKSTRUCT* param = (KBDLLHOOKSTRUCT*)lParam;
                DWORD vkCode = param->vkCode;

                // Acquire mutex lock before accessing shared resource (key events queue)
                //std::lock_guard<std::mutex> lock(keyboardEventsMutex);
                keyboardEventsMutex.lock();

                // Add the key event to the queue for asynchronous processing
                keyboardEvents.push({ wParam, vkCode });
                keyboardEventsMutex.unlock();
            }
        }

        // Call the next hook in the hook chain
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    void InputSystem::Run()
    {
        hHook = SetWindowsHookEx(WH_KEYBOARD_LL, InputSystem::KeyboardProc, NULL, 0);
        if (hHook == nullptr) {
            std::cerr << "Failed to install hook" << std::endl;
            return;
        }

        // Create a separate thread for input processing
        std::thread inputProcessingThread(&InputSystem::ProcessInputEvents, this);

        // Main loop for message processing
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Stop the input processing thread
        bInputProcessingThreadActive = false;
        inputProcessingThread.join();

        Stop();
    }

    void InputSystem::ProcessInputEvents()
    {
        while (bInputProcessingThreadActive)
        {
            // Acquire mutex lock before accessing shared resource (key events queue)
            //std::lock_guard<std::mutex> lock(keyboardEventsMutex);
            keyboardEventsMutex.lock();

            // Process input events asynchronously
            while (!keyboardEvents.empty()) {
                std::cout << "Size: " << keyboardEvents.size() << std::endl;
                KeyEvent keyEvent = keyboardEvents.front();
                keyboardEvents.pop();
                std::cout << "Key down: " << keyEvent.vkCode << std::endl;

                // Handle key event
                if (keyEvent.wParam == WM_KEYDOWN) {
                    std::cout << "Key down: " << keyEvent.vkCode << std::endl;
                } else if (keyEvent.wParam == WM_KEYUP) {
                    std::cout << "Key up: " << keyEvent.vkCode << std::endl;
                }
            }
            keyboardEventsMutex.unlock();

            // Add a short delay to prevent high CPU usage
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void InputSystem::Stop()
    {
        UnhookWindowsHookEx(hHook);
    }

    InputSystem::InputSystem()
    {

    }

    InputSystem::~InputSystem()
    {

    }

} // Engine
