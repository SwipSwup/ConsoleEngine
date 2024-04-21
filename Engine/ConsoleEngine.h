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

    struct EngineSettings
    {
        bool showFps = true;
        bool showRenderUpdates = false;

        int ticksPerSecond = 30;
        float fpsUpdateInterval = .1;
    };

    class ConsoleEngine
    {
    public:
        ConsoleEngine();
        virtual ~ConsoleEngine();

        void Start();
        void Stop();

    private:
        EngineSettings settings;

        void Run();

        void Tick();

        void FixedTick();

        void TickScene(float deltaTime);
        void FixTickScene();

    public:
        EngineSettings* GetSettings();
        void LoadSettings();
        void LoadSettings(EngineSettings settings);

    private:
        Scene* activeScene;

        void LoadDefaultScene();

        void UpdateConsoleTitle(float deltaTime = 0);

    public:
        bool LoadScene(Scene* scene);

    private:
        Window* window;
        Debug* debugConsole;

    public:
        Window* GetWindow();

        Vector2D GetWindowDimensions();
    };
} // Engine

#endif //CONSOLEENGINE_H
