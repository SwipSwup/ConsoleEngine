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

    void FixTick();

private:
    ConsoleEngine* engine;

    const char* name;

public:
    ConsoleEngine* GetEngine();

    const char* GetName();
private:
    std::list<GameObject*> loadedGameObjects;

public:
    void Spawn(GameObject* gameObject);
};

} // Engine

#endif //SCENE_H
