#include "Engine/ConsoleEngine.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/Vector2D.h"
#include "Engine/Window/Window.h"

int main()
{
    //Engine::Window w = Engine::Window(100, 25, true);
    //w.Render();

    /*char*** renderData = new char**[1]
    {
        new char*[1] {(char*) "A"},
    };

    char*** renderData2 = new char**[3]
    {
        new char*[3] {(char*) "+", (char*) "-", (char*) "+"},
        new char*[3] {(char*) "|", (char*) " ", (char*) "|"},
        new char*[3] {(char*) "+", (char*) "-", (char*) "+"}
    };

    //Engine::Sprite sprite = Engine::Sprite(texture, new Engine::Vector2D(1, 1));

    w.PushRenderData(renderData2, Engine::Vector2D(3, 3), Engine::Vector2D(0, 0));
    w.PushRenderData(renderData, Engine::Vector2D(1, 1), Engine::Vector2D(1, 1));
    w.Render();*/

    Engine::ConsoleEngine engine = Engine::ConsoleEngine();
    Engine::Scene* scene = new Engine::Scene((char*)"untitled");

    engine.LoadScene(scene);
    engine.Start();

    //TODO temporary so external window doesnt close;
    while(true);
}
