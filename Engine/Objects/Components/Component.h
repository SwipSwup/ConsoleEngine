//
// Created by david on 03/03/2024.
//

#ifndef COMPONENT_H
#define COMPONENT_H


namespace Engine
{
    class GameObject;

    class Component
    {
    private:
        GameObject* root;

    public:
        Component(GameObject* root);

    protected:
        virtual ~Component();

    public:
        virtual void Tick(float deltaTime);
        virtual void FixTick();


    };
}


#endif //COMPONENT_H
