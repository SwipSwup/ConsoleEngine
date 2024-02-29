#include <iostream>

#include "Engine/ConsoleEngine.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/Vector2D.h"
#include "Engine/Utility/Sprites/Sprite.h"
#include "Engine/Window/Window.h"

int main()
{
    //Engine::Window w = Engine::Window(100, 25, true);

    /*char** texture = new char*[3]
    {
        new char[3] {'+', '^', '+',},
        new char[3] {'|', ' ', '>',},
        new char[3] {'+', '-', '+',}
    };

    Engine::Color** color = new Engine::Color*[3]
    {
        new Engine::Color[3] {Engine::Color::BLU, Engine::Color::RED, Engine::Color::BLU},
        new Engine::Color[3] {Engine::Color::BLU, Engine::Color::BLU, Engine::Color::GRN},
        new Engine::Color[3] {Engine::Color::BLU, Engine::Color::BLU, Engine::Color::BLU},
    };

    Engine::Color** color2 = new Engine::Color*[3]
    {
        new Engine::Color[3] {Engine::Color::WHT, Engine::Color::WHT, Engine::Color::WHT},
        new Engine::Color[3] {Engine::Color::WHT, Engine::Color::WHT, Engine::Color::WHT},
        new Engine::Color[3] {Engine::Color::WHT, Engine::Color::WHT, Engine::Color::WHT},
    };*/

    /*char** texture = new char*[1]
    {
        new char[1] {'#'},
    };

    Engine::Color colors[5] = {Engine::Color::RED, Engine::Color::GRN, Engine::Color::YEL, Engine::Color::BLU, Engine::Color::MAG};

    Engine::Color** color = new Engine::Color*[1]
    {
        new Engine::Color[1] {Engine::Color::BLU},
    };

    Engine::Sprite* sprite = new Engine::Sprite(texture, color, Engine::Vector2D(3, 3));*/

    /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error getting console handle" << std::endl;
        return 1;
    }

    // Enable ANSI escape code support
    DWORD dwMode = 0;
    if (!GetConsoleMode(hConsole, &dwMode)) {
        std::cerr << "Error getting console mode" << std::endl;
        return 1;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hConsole, dwMode)) {
        std::cerr << "Error setting console mode" << std::endl;
        return 1;
    }

    // ANSI escape codes for changing text color
    const char* redText = "\x1b[31mRed text\x1b[0m\n"; // Red text
    const char* greenText = "\x1b[32mGreen text\x1b[0m\n"; // Green text

    // Write colored text directly to the console buffer
    DWORD charsWritten;
    if (!WriteConsoleA(hConsole, redText, strlen(redText), &charsWritten, NULL)) {
        std::cerr << "Error writing to console" << std::endl;
        return 1;
    }
    if (!WriteConsoleA(hConsole, greenText, strlen(greenText), &charsWritten, NULL)) {
        std::cerr << "Error writing to console" << std::endl;
        return 1;
    }*/

    /*char*** renderData = new char**[1]
    {
        new char*[1] {(char*) "A"},
    };

    char*** renderData2 = new char**[3]
    {
        new char*[3] {(char*) "+", (char*) "-", (char*) "+"},
        new char*[3] {(char*) "|", (char*) " ", (char*) "|"},
        new char*[3] {(char*) "+", (char*) "-", (char*) "+"}
    };

    //Engine::Sprite sprite = Engine::Sprite(texture, new Engine::Vector2D(1, 1));

    w.PushRenderData(renderData2, Engine::Vector2D(3, 3), Engine::Vector2D(0, 0));
    w.PushRenderData(renderData, Engine::Vector2D(1, 1), Engine::Vector2D(1, 1));
    w.Render();*/

    Engine::ConsoleEngine engine = Engine::ConsoleEngine();
    Engine::Scene* scene = new Engine::Scene((char*)"untitled");

    engine.LoadScene(scene);
    engine.Start();


    //TODO temporary so external window doesnt close;
    while(true);
}
