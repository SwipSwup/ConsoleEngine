#include <iostream>

#include "Engine/ConsoleEngine.h"
#include "Engine/Scene/Scene.h"

int main()
{
    srand (time(nullptr));

    Engine::ConsoleEngine engine = Engine::ConsoleEngine();
    Engine::Scene* scene = new Engine::Scene((char*)"untitled");


    engine.LoadScene(scene);
    engine.Start();

    //TODO temporary so external window doesnt close;
    while(true);
}
