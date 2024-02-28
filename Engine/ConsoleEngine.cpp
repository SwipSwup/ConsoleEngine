//
// Created by david on 24/02/2024.
//

#include "ConsoleEngine.h"

#include <chrono>
#include <iostream>

#include "Scene/Scene.h"
#include "Utility/Vector2D.h"
#include "Window/Window.h"

namespace Engine {
    ConsoleEngine::ConsoleEngine()
    {
        this->window = new Window(100, 25, true);

        ticksPerSecond = 1;



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
        FixTickScene();
        //std::cout << currentTimePoint.time_since_epoch().count();

    }

    void ConsoleEngine::FixedTick()
    {
        FixTickScene();
    }

    short x = 0;
    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);

        char*** renderData = new char**[1]
        {
            new char*[1] {(char*) "A"},
        };

        char*** renderData2 = new char**[3]
        {
            new char*[3] {(char*) "+", (char*) "^", (char*) "+"},
            new char*[3] {(char*) "|", (char*) " ", (char*) "|"},
            new char*[3] {(char*) "+", (char*) "-", (char*) "+"}
        };

        //Engine::Sprite sprite = Engine::Sprite(texture, new Engine::Vector2D(1, 1));

        window->PushRenderCall(RenderCall{
            COORD {x, 0},
            COORD {3, 3},
            renderData2
        });

        window->PushRenderCall(RenderCall{
            COORD {99, 24},
            COORD {1, 1},
            renderData
        });

        window->Render();

    }

    void ConsoleEngine::FixTickScene()
    {


        x++;

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