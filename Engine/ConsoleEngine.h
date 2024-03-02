//
// Created by david on 24/02/2024.
//

#ifndef CONSOLEENGINE_H
#define CONSOLEENGINE_H
#include <string>

namespace Engine
{
    class Debug;
}

namespace Engine
{
    struct Vector2D;
}

namespace Engine
{
    class Window;
    class Scene;
}

namespace Engine {

class ConsoleEngine {
public:
    ConsoleEngine();

    void Start();

private:
    void Run();

    void Stop();

    int ticksPerSecond;
    void Tick();

    void FixedTick();

    void TickScene(float deltaTime);
    void FixTickScene();

public:
    void SetTicksPerSecond(int tps);

private:
    Scene* activeScene;

public:
    bool LoadScene(Scene* scene);

private:
    Window* window;
    Debug* debugConsole;

public:
    Vector2D GetWindowDimensions();
    //void PushRenderData(char** )

};

} // Engine

#endif //CONSOLEENGINE_H
