#include <iostream>

#include "Engine/ConsoleEngine.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Objects/Components/DefaultComponents/SpriteRenderComponent.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/Vector2D.h"

//https://www.charset.org/utf-8
int main()
{
    srand (time(nullptr));

    Engine::ConsoleEngine engine = Engine::ConsoleEngine();
    Engine::Scene* scene = new Engine::Scene((char*)"untitled");

    Engine::GameObject object = Engine::GameObject(scene);
    object.position = new Engine::Vector2D(4, 5);

    Engine::SpriteRenderComponent* c = object.AddComponent<Engine::SpriteRenderComponent>();

    engine.LoadScene(scene);
    engine.Start();

    //TODO temporary so external window doesnt close;
    while(true);
}
/*
int t = 0;
t++;

char** texture = new char*[3]
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

        window->WDrawSprite(sprite, i, 0, 2);

for (int x = 0; x < window->GetWindowXDimension(); ++x)
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
}

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

 */