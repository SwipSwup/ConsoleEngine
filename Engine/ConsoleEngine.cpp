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

    int t = 0;
    void ConsoleEngine::FixTickScene()
    {
    t++;
        for (int x = 0; x < window->GetWindowXDimension(); ++x)
        {
            for (int y = 0; y < window->GetWindowYDimension(); ++y)
            {
                double minDistance = DBL_MAX;
                int closestSeedIndex = -1;

                for (size_t i = 0; i < seedPoints.size(); ++i)
                {
                    Vector2D modifiedSeedPoint = seedPoints[i];
                    modifiedSeedPoint.x += (int)(0.5 + 5.0 * sin(t * .1 + 6.2831 * 0.3 + modifiedSeedPoint.x));
                    modifiedSeedPoint.y += (int)(0.5 + 5.0 * sin(t * .1 + 6.2831 * 0.7 + modifiedSeedPoint.y));

                    double distance = Vector2D(x, y).Distance(modifiedSeedPoint);
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        closestSeedIndex = i;
                    }
                }

                Color** color3 = new Color*[1];
                color3[0] = new Color[1]{
                    colors[(closestSeedIndex + (std::hash<int>()(seedPoints[closestSeedIndex].x) ^ std::hash<int>()(
                        seedPoints[closestSeedIndex].y)) / (MAXINT / 2)) % 12]
                };

                sprite2->Load2DColor(color3);
                window->WDrawSprite(sprite2, x, y, 1);
            }
        }
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
