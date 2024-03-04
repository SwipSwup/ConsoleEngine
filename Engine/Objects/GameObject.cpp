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

    void GameObject::SetScene(Scene* scene)
    {
        this->scene = scene;
    }

    /*Vector3D* GameObject::GetPosition()
    {
        return position;
    }

    void GameObject::SetPosition(Vector3D position)
    {
        delete this->position;
        this->position = new Vector3D(position);
    }*/

    void GameObject::TickComponents(float deltaTime)
    {
        for (Component* component : components)
        {
            component->Tick(deltaTime);
        }
    }

    void GameObject::FixTickComponents()
    {
        for (Component* component : components)
        {
            component->FixTick();
        }
    }

    void GameObject::Tick(float deltaTime)
    {
        TickComponents(deltaTime);

    }

    void GameObject::FixTick()
    {
        FixTickComponents();

        //*position += Vector3D(1, 1, 0);
    }

    void GameObject::OnSpawn()
    {
        for (Component* component : components)
        {
            component->SetRoot(this);
            component->OnSpawn();
        }
    }
} // Engine