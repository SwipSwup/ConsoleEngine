//
// Created by david on 24/02/2024.
//

#include "ConsoleEngine.h"

#include <cfloat>
#include <chrono>
#include <cmath>
#include <iostream>
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
            int randX = rand() % window->GetWindowXDimension();
            int randY = rand() % window->GetWindowYDimension();
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

    int t = 0;

    void ConsoleEngine::TickScene(float deltaTime)
    {
        activeScene->Tick(deltaTime);
    }

    Engine::Color colors[] = {
        Engine::Color::RED, Engine::Color::GRN, Engine::Color::YEL, Engine::Color::BLU, Engine::Color::MAG, Color::CYN,
        Engine::Color::HRED, Engine::Color::HGRN, Engine::Color::HYEL, Engine::Color::HBLU, Engine::Color::HMAG,
        Color::HCYN
    };
    char** texture3 = new char*[1]
    {
        new char[1]{'#'},
    };
    Engine::Sprite* sprite2 = new Engine::Sprite(texture3, nullptr, Engine::Vector2D(1, 1));


    void ConsoleEngine::FixTickScene()
    {
        t++;

        /*char** texture = new char*[3]
        {
            new char[3]{'+', '^', '+',},
            new char[3]{'|', ' ', '>',},
            new char[3]{'+', '-', '+',}
        };

        Engine::Color** color = new Engine::Color*[3]
        {
            new Engine::Color[3]{Engine::Color::BLU, Engine::Color::RED, Engine::Color::BLU},
            new Engine::Color[3]{Engine::Color::BLU, Engine::Color::BLU, Engine::Color::GRN},
            new Engine::Color[3]{Engine::Color::BLU, Engine::Color::BLU, Engine::Color::BLU},
        };

        Sprite* sprite = new Sprite(texture, color, Vector2D(3, 3));

        window->WDrawSprite(sprite, i, 0, 2);*/

        /*for (int x = 0; x < window->GetWindowXDimension(); ++x)
        {
            for (int y = 0; y < window->GetWindowYDimension(); ++y)
            {
                int xuv = x / window->GetWindowXDimension();
                int yuv = y / window->GetWindowYDimension();

                int col = (0.5 + 0.5 * std::cos(t + xuv + yuv)) * 6;


                Engine::Color** color3 = new Engine::Color*[1]
                {
                    new Engine::Color[1]{colors[(col) % 6]},
                };

                sprite2->Load2DColor(color3);
                window->WDrawSprite(sprite2, x, y, 1);
                std::ostringstream ostr;
                ostr << "x: " << col;
                window->WDrawText(ostr.str().c_str(), 0, 0, 2);
            }
        }*/

        for (int x = 0; x < window->GetWindowXDimension(); ++x)
        {
            for (int y = 0; y < window->GetWindowYDimension(); ++y)
            {
                // Calculate the distances to each seed point
                double minDistance = DBL_MAX;
                int closestSeedIndex = -1;

                for (size_t i = 0; i < seedPoints.size(); ++i)
                {
                    // Add time component to the seed point coordinates
                    Vector2D modifiedSeedPoint = seedPoints[i];
                    modifiedSeedPoint.x += (0.5 + 5.0 * sin(t * .1 + 6.2831 * 0.3 + modifiedSeedPoint.x));
                    // You can adjust how time affects the seed points
                    modifiedSeedPoint.y += (0.5 + 5.0 * sin(t * .1 + 6.2831 * 0.7 + modifiedSeedPoint.y));

                    double distance = Vector2D(x, y).Distance(modifiedSeedPoint);
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        closestSeedIndex = i;
                    }
                }

                // Assign the cell to the region corresponding to the closest seed point
                Engine::Color** color3 = new Engine::Color*[1];
                color3[0] = new Engine::Color[1]{
                    colors[(closestSeedIndex + (std::hash<int>()(seedPoints[closestSeedIndex].x) ^ std::hash<int>()(
                        seedPoints[closestSeedIndex].y)) / (MAXINT / 2)) % 12]
                };

                // Draw the cell with the assigned color
                sprite2->Load2DColor(color3);
                window->WDrawSprite(sprite2, x, y, 1);

                // Debug: Show the closest seed index
                std::ostringstream ostr;
                ostr << "Seed Index: " << closestSeedIndex;
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
