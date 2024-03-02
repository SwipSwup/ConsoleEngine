//
// Created by david on 24/02/2024.
//

#include "ConsoleEngine.h"

#include <chrono>
#include <iostream>
#include <sstream>

#include "Scene/Scene.h"
#include "Utility/Vector2D.h"
#include "Utility/Sprites/Sprite.h"
#include "Window/Window.h"

namespace Engine {
    ConsoleEngine::ConsoleEngine()
    {
        this->window = new Window(1000, 250, true);

        ticksPerSecond = 30;
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

        }
    }

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
        window->Render();
    }

    int i = 0;
    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);
    }

    void ConsoleEngine::FixTickScene()
    {
        char** texture = new char*[3]
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

        Sprite* sprite = new Sprite(texture, color, Vector2D(3, 3));

        window->WDrawSprite(sprite, i, 0, 2);
        i++;
        Engine::Color colors[5] = {Engine::Color::RED, Engine::Color::GRN, Engine::Color::YEL, Engine::Color::BLU, Engine::Color::MAG};

    Engine::Color** color2 = new Engine::Color*[1]
    {
        new Engine::Color[1] {Engine::Color::BLU},
    };

    char** texture3 = new char*[1]
    {
        new char[1] {'#'},
    };

    Engine::Sprite* sprite2 = new Engine::Sprite(texture3, color2, Engine::Vector2D(1, 1));

        for (int x = 0; x < window->GetWindowXDimension(); ++x)
        {
            for (int y = 0; y < window->GetWindowYDimension(); ++y)
            {
                Engine::Color** color3 = new Engine::Color*[1]
                {
                    new Engine::Color[1] {colors[((x + i)/25)  % 5]},
                };

                sprite2->Load2DColor(color3);
                window->WDrawSprite(sprite2, x, y, 1);
                std::ostringstream ostr;
                ostr << "x: " << i;
                window->WDrawText(ostr.str().c_str(), 0, 0, 2);
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

    Vector2D ConsoleEngine::GetWindowDimensions()
    {
        return Vector2D(window->GetWindowXDimension(), window->GetWindowYDimension());
    }
} // Engine