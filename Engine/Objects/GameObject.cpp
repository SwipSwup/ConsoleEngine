//
// Created by david on 24/02/2024.
//

#include "GameObject.h"

#include <conio.h>

#include "../Utility/Vector3D.h"

namespace Engine
{
    GameObject::GameObject(Scene* root)
    {
        scene_ref = root;

        position = new Vector3D(0, 0, 0);
    }

    Scene* GameObject::GetScene()
    {
        return scene_ref;
    }

    void GameObject::SetScene(Scene* scene)
    {
        this->scene_ref = scene;
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

        if (kbhit())
        {
            char nextMove = _getch();
            switch (nextMove)
            {
            case 'w':
                *position += Vector3D(0, 1, 0);
                break;
            case 'a':
                *position += Vector3D(-1, 0, 0);
                break;
            case 's':
                *position += Vector3D(0, -1, 0);
                break;
            case 'd':
                *position += Vector3D(1, 0, 0);
                break;
            }
        }
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
