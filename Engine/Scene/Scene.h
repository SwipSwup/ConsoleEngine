//
// Created by david on 24/02/2024.
//

#ifndef SCENE_H
#define SCENE_H
#include <list>

namespace Engine {
    class GameObject;
    class ConsoleEngine;

class Scene {
public:
    Scene(char* name);

    void OnSceneLoad(ConsoleEngine* engine);

    void Tick(float deltaTime);

private:
    ConsoleEngine* engine;

public:
    void Spawn(GameObject* gameObject);

private:
    std::list<GameObject*> loadedGameObjects;
};

} // Engine

#endif //SCENE_H
