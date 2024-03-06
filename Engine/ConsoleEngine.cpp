//
// Created by david on 24/02/2024.
//

#include "ConsoleEngine.h"

#include <chrono>
#include <sstream>

#include "Debug/Debug.h"
#include "Scene/Scene.h"
#include "Utility/Vector2D.h"
#include "Window/Window.h"

namespace Engine
{
    ConsoleEngine::ConsoleEngine()
    {
        this->window = new Window(100, 30);
        this->debugConsole = new Debug();

        activeScene = nullptr;
        settings = EngineSettings();

    }

    ConsoleEngine::~ConsoleEngine()
    {
        delete window;
        delete debugConsole;
    }

    std::chrono::steady_clock::time_point previousTimePoint;

    void ConsoleEngine::Start()
    {
        previousTimePoint = std::chrono::steady_clock::now();

        if(activeScene == nullptr)
            LoadDefaultScene();

        LoadSettings();

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

            window->Render();
        }
    }

    void ConsoleEngine::Tick()
    {
        if(activeScene == nullptr)
        {
            return;
        }

        std::chrono::steady_clock::time_point currentTimePoint = std::chrono::steady_clock::now();
        TickScene((float)(currentTimePoint - previousTimePoint).count());

        if ((currentTimePoint - previousTimePoint).count() < std::chrono::duration_cast<
            std::chrono::steady_clock::duration>(std::chrono::duration<float>(1.0f / settings.ticksPerSecond)).count())
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

        window->UpdateConsoleTitle(activeScene->GetName());
    }

    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);

        //todo do this in the title
        std::ostringstream ostr;
        ostr << "DeltaTime: " << deltaTime / 1000.f;
        window->WDrawText(ostr.str().c_str(), 0, 0, 2);
    }

    void ConsoleEngine::FixTickScene()
    {
        activeScene->FixTick();
    }

    EngineSettings* ConsoleEngine::GetSettings()
    {
        return &settings;
    }

    void ConsoleEngine::LoadSettings()
    {
        window->ShowRenderUpdates(settings.showRenderUpdates);

    }

    void ConsoleEngine::LoadSettings(EngineSettings settings)
    {
        this->settings = settings;
        LoadSettings();
    }

    void ConsoleEngine::LoadDefaultScene()
    {
        LoadScene(new Scene("default"));
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

    Window* ConsoleEngine::GetWindow()
    {
        return window;
    }

    Vector2D ConsoleEngine::GetWindowDimensions()
    {
        return Vector2D(window->GetWindowXDimension(), window->GetWindowYDimension());
    }
} // Engine
