//
// Created by david on 24/02/2024.
//

#ifndef CONSOLEENGINE_H
#define CONSOLEENGINE_H

namespace Engine
{
    struct Vector2D;

    class Debug;
    class Window;
    class Scene;

    class ConsoleEngine
    {
    public:
        ConsoleEngine();
        virtual ~ConsoleEngine();

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
        Window* GetWindow();

        Vector2D GetWindowDimensions();
        //void PushRenderData(char** )
    };
} // Engine

#endif //CONSOLEENGINE_H
