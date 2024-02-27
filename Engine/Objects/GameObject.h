//
// Created by david on 24/02/2024.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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

    private:
        Scene* scene;

        char** texture;
    public:
        Vector2D* position;

    public:
        virtual void Tick(float deltaTime);

        virtual void OnSpawn();
    };
} // Engine

#endif //GAMEOBJECT_H
