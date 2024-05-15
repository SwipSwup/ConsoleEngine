cmake_minimum_required(VERSION 3.28)
project(ConsoleEngine)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(ConsoleEngine main.cpp
        Engine/Scene/Scene.cpp
        Engine/Scene/Scene.h
        Engine/Objects/GameObject.cpp
        Engine/Objects/GameObject.h
        Engine/ConsoleEngine.cpp
        Engine/ConsoleEngine.h
        Engine/Window/Window.cpp
        Engine/Window/Window.h
        Engine/Utility/Vector2D.cpp
        Engine/Utility/Vector2D.h
        Engine/Utility/Sprites/Sprite.cpp
        Engine/Utility/Sprites/Sprite.h
        Engine/Utility/Color.cpp
        Engine/Utility/Color.h
        Engine/Utility/Vector3D.cpp
        Engine/Utility/Vector3D.h
        Engine/Debug/Debug.cpp
        Engine/Debug/Debug.h
        Engine/Objects/Components/Component.cpp
        Engine/Objects/Components/Component.h
        Engine/Objects/Components/DefaultComponents/SpriteRenderComponent.cpp
        Engine/Objects/Components/DefaultComponents/SpriteRenderComponent.h
        Engine/Objects/Components/DefaultComponents/TextRenderComponent.cpp
        Engine/Objects/Components/DefaultComponents/TextRenderComponent.h
        Engine/InputSystem/InputSystem.cpp
        Engine/InputSystem/InputSystem.h
        Engine/InputSystem/InputAction.cpp
        Engine/InputSystem/InputAction.h
        Engine/Utility/EventSystem/Event.cpp
        Engine/Utility/EventSystem/Event.h
)

