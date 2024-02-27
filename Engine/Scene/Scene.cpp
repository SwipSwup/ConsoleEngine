//
// Created by david on 24/02/2024.
//

#include "Scene.h"

#include "../Objects/GameObject.h"

namespace Engine {
    Scene::Scene(char* name = "untitled")
    {

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

        //render data pushen

    }

    void Scene::Spawn(GameObject* gameObject)
    {
        loadedGameObjects.push_front(gameObject);
    }
} // Engine