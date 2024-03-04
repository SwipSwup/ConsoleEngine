//
// Created by david on 03/03/2024.
//

#include "SpriteRenderComponent.h"

#include <iostream>

#include "../../GameObject.h"
#include "../../../ConsoleEngine.h"
#include "../../../Scene/Scene.h"
#include "../../../Utility/Vector3D.h"
#include "../../../Window/Window.h"

namespace Engine
{
    void SpriteRenderComponent::Tick(float deltaTime)
    {
        Component::Tick(deltaTime);

        window->WDrawSprite(sprite, root->position->x, root->position->y, root->position->z);
    }

    void SpriteRenderComponent::OnSpawn()
    {
        Component::OnSpawn();

        window = root->GetScene()->GetEngine()->GetWindow();
    }
} // Engine
