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

        window_ref->WDrawSprite(sprite_ref, root_ref->position->x, root_ref->position->y, root_ref->position->z);
    }

    void SpriteRenderComponent::OnSpawn()
    {
        Component::OnSpawn();

        window_ref = root_ref->GetScene()->GetEngine()->GetWindow();
    }
} // Engine
