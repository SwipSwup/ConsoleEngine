//
// Created by david on 24/02/2024.
//

#include "GameObject.h"

#include <iostream>

#include "../Utility/Vector3D.h"

namespace Engine {
    GameObject::GameObject(Scene* root)
    {
        scene = root;

        position = new Vector3D(0, 0, 0);
    }

    Scene* GameObject::GetScene()
    {
        return scene;
    }

    void GameObject::Tick(float deltaTime)
    {

    }

    void GameObject::FixTick()
    {
    }

    void GameObject::OnSpawn()
    {
    }
} // Engine