//
// Created by david on 24/02/2024.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <list>

namespace Engine
{
    class Component;
}

namespace Engine
{
    class Scene;
    struct Vector2D;
}

namespace Engine
{
    class GameObject
    {
    public:
        explicit GameObject(Scene* root);
        Vector2D* position;

    private:
        Scene* scene;
        std::list<Component*> components;

    public:
        template <typename T>
        T* AddComponent();


    public:
        virtual void Tick(float deltaTime);

        virtual void FixTick();

        virtual void OnSpawn();
    };


} // Engine

#endif //GAMEOBJECT_H
