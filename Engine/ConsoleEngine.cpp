//
// Created by david on 24/02/2024.
//

#include "ConsoleEngine.h"

#include <chrono>

#include "Scene/Scene.h"
#include "Utility/Vector2D.h"
#include "Utility/Sprites/Sprite.h"
#include "Window/Window.h"

namespace Engine {
    ConsoleEngine::ConsoleEngine()
    {
        this->window = new Window(100, 25, true);

        ticksPerSecond = 60;
    }

    std::chrono::steady_clock::time_point previousTimePoint;
    void ConsoleEngine::Start()
    {
        previousTimePoint = std::chrono::steady_clock::now();

        Run();
    }

    void ConsoleEngine::Stop()
    {

    }

    void ConsoleEngine::Run()
    {
        while(true)
        {
            Tick();

            window->Render();
        }
    }

    float tickTimer;
    void ConsoleEngine::Tick()
    {
        std::chrono::steady_clock::time_point currentTimePoint = std::chrono::steady_clock::now();
        TickScene((float) (currentTimePoint - previousTimePoint).count());

        if((currentTimePoint - previousTimePoint).count() < std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<float>(1.0f / ticksPerSecond)).count())
        {
            return;
        }

        previousTimePoint = currentTimePoint;
        FixedTick();
        //std::cout << currentTimePoint.time_since_epoch().count();

    }

    void ConsoleEngine::FixedTick()
    {
        FixTickScene();

    }

    Engine::Color colors[5] = {Engine::Color::RED, Engine::Color::GRN, Engine::Color::YEL, Engine::Color::BLU, Engine::Color::MAG};

    Engine::Color** color = new Engine::Color*[1]
    {
        new Engine::Color[1] {Engine::Color::BLU},
    };

    char** texture = new char*[1]
    {
        new char[1] {'#'},
    };

    Engine::Sprite* sprite = new Engine::Sprite(texture, color, Engine::Vector2D(1, 1));

    int i = 0;
    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);
    }

    void ConsoleEngine::FixTickScene()
    {
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


        //window->PushSprite(0, 0, 1, sprite);

        i++;
        for (int x = 0; x < 100; ++x)
        {
            for (int y = 0; y < 25; ++y)
            {
                Engine::Color** color = new Engine::Color*[1]
                {
                    new Engine::Color[1] {colors[((x + i)/25)  % 5]},
                };

                sprite->Load2DColor(color);
                window->PushSprite(x, y, 1, sprite);
            }
        }
    }

    void ConsoleEngine::SetTicksPerSecond(int tps)
    {
        ticksPerSecond = tps;
    }

    bool ConsoleEngine::LoadScene(Scene* scene)
    {
        if(scene == nullptr)
        {
            return false;
        }

        scene->OnSceneLoad(this);
        activeScene = scene;
        return true;
    }

} // Engine