cmake_minimum_required(VERSION 3.28)
project(ConsoleEngine)

set(CMAKE_CXX_STANDARD 17)

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
        Engine/Utility/Colors.h
        Engine/Utility/Sprite.cpp
        Engine/Utility/Sprite.h
)
