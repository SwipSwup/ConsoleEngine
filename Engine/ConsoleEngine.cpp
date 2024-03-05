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

            //window->Render();
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
    }

    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);

        std::ostringstream ostr;
        ostr << "DeltaTime: " << deltaTime / 1000.f;
        window->WDrawText(ostr.str().c_str(), 0, 0, 2);
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


    int t = 0;

    void ConsoleEngine::FixTickScene()
    {
        activeScene->FixTick();
        t++;

        int windowX = window->GetWindowXDimension();
        int windowY = window->GetWindowYDimension();

        for (int x = 0; x < windowX; ++x) {
            for (int y = 0; y < windowY; ++y) {
                double uvx = static_cast<double>(x) / windowX;
                double uvy = static_cast<double>(y) / windowY;

                double r = 0.5 + 0.5 * cos(t * 0.1 + uvx);
                double g = 0.5 + 0.5 * sin(t * 0.1 + uvy + 2.0);
                double b = 0.5 + 0.5 * cos(t * 0.1 + uvx + 4.0);

                r = std::max(0.0, std::min(r, 1.0));
                g = std::max(0.0, std::min(g, 1.0));
                b = std::max(0.0, std::min(b, 1.0));

                int red = static_cast<int>(r * 255);
                int green = static_cast<int>(g * 255);
                int blue = static_cast<int>(b * 255);

                Color color = Color(red, green, blue);

                Color** colorArray = new Color*[1];
                colorArray[0] = new Color[1]{color};
                sprite2->Load2DColor(colorArray);
                window->WDrawSprite(sprite2, x, y, 1);

                delete[] colorArray[0];
                delete[] colorArray;
            }
        }
        window->Render();
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

    Window* ConsoleEngine::GetWindow()
    {
        return window;
    }

    Vector2D ConsoleEngine::GetWindowDimensions()
    {
        return Vector2D(window->GetWindowXDimension(), window->GetWindowYDimension());
    }
} // Engine
