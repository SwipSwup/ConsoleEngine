//
// Created by david on 02/03/2024.
//

#include "Debug.h"

#include <cstdio>
#include <windows.h>

namespace Engine {
    Debug::Debug()
    {
    }

    void Debug::Init()
    {
        // Allocate a new console for this process
        AllocConsole();

        // Attach the standard input, output, and error streams to the new console
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
} // Engine