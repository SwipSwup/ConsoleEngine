//
// Created by david on 03/03/2024.
//

#include "SpriteRenderComponent.h"

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

        //todo this is not optimal
        root->GetScene()->GetEngine()->GetWindow()->WDrawSprite(sprite, root->position->x, root->position->y, root->position->z);
    }
} // Engine
