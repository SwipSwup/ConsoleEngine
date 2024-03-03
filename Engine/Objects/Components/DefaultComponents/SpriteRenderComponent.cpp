//
// Created by david on 03/03/2024.
//

#include "SpriteRenderComponent.h"

#include "../../GameObject.h"

namespace Engine {
    void SpriteRenderComponent::Tick(float deltaTime)
    {
        Component::Tick(deltaTime);

        root->GetScene()
    }
} // Engine