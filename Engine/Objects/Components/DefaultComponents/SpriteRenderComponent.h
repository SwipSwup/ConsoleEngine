//
// Created by david on 03/03/2024.
//

#ifndef SPRITERENDERCOMPONENT_H
#define SPRITERENDERCOMPONENT_H
#include "../Component.h"

namespace Engine
{
    struct Sprite;

    class SpriteRenderComponent : public Component
    {
    public:
        Sprite* sprite;

        void Tick(float deltaTime) override;
    };
} // Engine

#endif //SPRITERENDERCOMPONENT_H
