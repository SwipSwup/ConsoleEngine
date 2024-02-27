//
// Created by david on 24/02/2024.
//

#include "GameObject.h"
#include "../Utility/Vector2D.h"

namespace Engine {
    GameObject::GameObject(Scene* root)
    {
        scene = root;

        position = new Vector2D(0, 0);
    }

    void GameObject::Tick(float deltaTime)
    {
    }

    void GameObject::OnSpawn()
    {
    }
} // Engine