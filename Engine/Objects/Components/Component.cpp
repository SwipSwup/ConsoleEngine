//
// Created by david on 03/03/2024.
//

#include "Component.h"

Engine::Component::Component(GameObject* root)
{
    this->root = root;
}

Engine::Component::~Component()
{
}

void Engine::Component::Tick(float deltaTime)
{
}

void Engine::Component::FixTick()
{
}
