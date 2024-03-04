//
// Created by david on 03/03/2024.
//

#include "Component.h"

Engine::Component::~Component()
{
}

void Engine::Component::SetRoot(GameObject* root)
{
    this->root = root;
}

void Engine::Component::Tick(float deltaTime)
{
}

void Engine::Component::FixTick()
{
}

void Engine::Component::OnSpawn()
{
}
