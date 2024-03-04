//
// Created by david on 03/03/2024.
//

#ifndef SPRITERENDERCOMPONENT_H
#define SPRITERENDERCOMPONENT_H
#include "../Component.h"

namespace Engine
{
    class Window;
    struct Sprite;

    class SpriteRenderComponent : public Component
    {
    private:
        Window* window;

    public:
        Sprite* sprite;

        void Tick(float deltaTime) override;

        void OnSpawn() override;
    };
} // Engine

#endif //SPRITERENDERCOMPONENT_H
