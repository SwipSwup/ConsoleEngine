//
// Created by david on 24/02/2024.
//

#include "GameObject.h"

#include <iostream>

#include "../Utility/Vector2D.h"
#include "Components/Component.h"

namespace Engine {
    GameObject::GameObject(Scene* root)
    {
        scene = root;

        position = new Vector2D(0, 0);
    }

    template <typename T>
    T* GameObject::AddComponent()
    {
        if(!std::is_same<T, Component>::value)
        {
            std::cerr << "Class " << typeid(T).name() << " is not of type Component";
            return nullptr;
        }

        T* component = new T(this);
        components.push_back(component);
        return component;
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