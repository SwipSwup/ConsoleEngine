//
// Created by david on 24/02/2024.
//

#include "ConsoleEngine.h"

#include <chrono>

#include "Scene/Scene.h"
#include "Utility/Vector2D.h"
#include "Window/Window.h"

namespace Engine {
    ConsoleEngine::ConsoleEngine()
    {
        this->window = new Window(Vector2D(100, 25), true);

        ticksPerSecond = 10;
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
        if(60.f / (float) ticksPerSecond > (float) (currentTimePoint - previousTimePoint).count())
        {
            return;
        }

        previousTimePoint = currentTimePoint;

        TickScene((float) (currentTimePoint - previousTimePoint).count());
    }

    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);
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

        window->ClearRenderBuffer();

        scene->OnSceneLoad(this);
        activeScene = scene;
        return true;
    }

} // Engine