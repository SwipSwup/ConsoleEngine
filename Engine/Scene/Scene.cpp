//
// Created by david on 24/02/2024.
//

#include "Scene.h"

#include <iostream>

#include "../Objects/GameObject.h"

namespace Engine {
    Scene::Scene(char* name)
    {
        this->name = name;
    }

    void Scene::OnSceneLoad(ConsoleEngine* engine)
    {
        this->engine = engine;
    }

    void Scene::Tick(float deltaTime)
    {
        for (GameObject* object : loadedGameObjects)
        {
            object->Tick(deltaTime);
        }
    }

    void Scene::FixTick()
    {
        for (GameObject* object : loadedGameObjects)
        {
            object->FixTick();
        }
    }

    void Scene::Spawn(GameObject* gameObject)
    {
        loadedGameObjects.push_back(gameObject);

        gameObject->SetScene(this);
        gameObject->OnSpawn();
    }

    ConsoleEngine* Scene::GetEngine()
    {
        return engine;
    }

    const char* Scene::GetName()
    {
        return name;
    }
} // Engine