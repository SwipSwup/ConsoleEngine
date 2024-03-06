//
// Created by david on 24/02/2024.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <list>

#include "Components/Component.h"

namespace Engine
{
    struct Vector3D;
    class Component;
    class Scene;

    class GameObject
    {
    public:
        GameObject(Scene* root);

        Vector3D* position;
    private:
        Scene* scene_ref;
        std::list<Component*> components;


    public:
        template <class T>
        T* AddComponent()
        {
            T* component = new T();
            components.push_back(component);
            return component;
        }

        template <class T>
        T* GetComponent()
        {
            for (Component* component : components)
            {
                if (std::is_base_of_v<Component, T>)
                {
                    return dynamic_cast<T>(component);
                }
            }

            return nullptr;
        }

        Scene* GetScene();

        void SetScene(Scene* scene);
    private:
        void TickComponents(float deltaTime);

        void FixTickComponents();

    public:
        virtual void Tick(float deltaTime);

        virtual void FixTick();

        virtual void OnSpawn();
    };
} // Engine

#endif //GAMEOBJECT_H
