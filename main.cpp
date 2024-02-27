#include "Engine/Scene/Scene.h"
#include "Engine/Utility/Sprite.h"
#include "Engine/Utility/Vector2D.h"
#include "Engine/Window/Window.h"

int main()
{
    Engine::Window w = Engine::Window(Engine::Vector2D(100, 25), true);

    char** texture = new char*[1]{ (char*)"n" };

    Engine::Sprite sprite = Engine::Sprite(texture, new Engine::Vector2D(1, 1));

    w.PushSpriteIntoRenderBuffer(&sprite, Engine::Vector2D(4,3));
    w.Render();

    delete texture[0];
    delete texture;
    //TODO temporary so external window doesnt close;
    while(true);
}
