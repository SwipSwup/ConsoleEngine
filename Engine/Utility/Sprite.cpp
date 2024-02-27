//
// Created by david on 27/02/2024.
//

#include "Sprite.h"

#include <iostream>

#include "Vector2D.h"

namespace Engine {
    Sprite::Sprite(char** data, Vector2D* size)
    {
        textureData = data;

        this->size = size;
    }

    Sprite::~Sprite()
    {
        delete size;
    }

    char* Sprite::GetTextureAndColorData(int x, int y)
    {
        if(x < 0 || x >= size->x || y < 0 || y >= size->y)
            return nullptr;

        return &textureData[y][x];
        //return colorData[y][x] + textureData[y][x];
    }
} // Engine