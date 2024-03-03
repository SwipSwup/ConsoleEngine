//
// Created by david on 24/02/2024.
//

#include "ConsoleEngine.h"

#include <cfloat>
#include <chrono>
#include <cmath>
#include <sstream>
#include <vector>

#include "Debug/Debug.h"
#include "Scene/Scene.h"
#include "Utility/Vector2D.h"
#include "Utility/Sprites/Sprite.h"
#include "Window/Window.h"

namespace Engine
{
    const int numSeedPoints = 20; // Adjust the number of seed points as needed
    std::vector<Vector2D> seedPoints;

    ConsoleEngine::ConsoleEngine()
    {
        this->window = new Window(100, 30, true);
        this->debugConsole = new Debug();

        ticksPerSecond = 30;

        for (int i = 0; i < numSeedPoints; ++i)
        {
            int randX = (rand() % (window->GetWindowXDimension() + 20)) - 10;
            int randY = (rand() % (window->GetWindowYDimension() + 20)) - 10;
            seedPoints.push_back(Vector2D(randX, randY));
        }
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
        while (true)
        {
            Tick();
        }
    }

    void ConsoleEngine::Tick()
    {
        std::chrono::steady_clock::time_point currentTimePoint = std::chrono::steady_clock::now();
        TickScene((float)(currentTimePoint - previousTimePoint).count());

        if ((currentTimePoint - previousTimePoint).count() < std::chrono::duration_cast<
            std::chrono::steady_clock::duration>(std::chrono::duration<float>(1.0f / ticksPerSecond)).count())
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


    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);
    }

    Color colors[] = {
        Color::RED, Color::GRN, Color::YEL, Color::BLU, Color::MAG, Color::CYN, Color::HRED, Color::HGRN, Color::HYEL,
        Color::HBLU, Color::HMAG, Color::HCYN
    };
    wchar_t** texture3 = new wchar_t*[1]
    {
        new wchar_t[1]{L'\u01CA'},
    };
    Sprite* sprite2 = new Sprite(texture3, nullptr, Vector2D(1, 1));


    void ConsoleEngine::FixTickScene()
    {
    }

    void ConsoleEngine::SetTicksPerSecond(int tps)
    {
        ticksPerSecond = tps;
    }

    bool ConsoleEngine::LoadScene(Scene* scene)
    {
        if (scene == nullptr)
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
