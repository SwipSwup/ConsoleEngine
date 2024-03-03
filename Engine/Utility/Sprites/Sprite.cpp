//
// Created by david on 27/02/2024.
//

#include "Sprite.h"

#include <iostream>

#include "../Vector2D.h"
#include "../Color.h"

namespace Engine
{
    Sprite::Sprite(wchar_t** texture, Vector2D textureDimensions)
    {
        Init(texture, nullptr, textureDimensions);
    }

    Sprite::Sprite(wchar_t** texture, Color** color, Vector2D textureDimensions)
    {
        Init(texture, color, textureDimensions);
    }

    Sprite::~Sprite()
    {
        delete textureDimensions;

        for (int y = 0; y < textureDimensions->y; ++y)
        {
            delete[] texture[y];
            delete[] color[y];
        }

        delete[] texture;
        delete[] color;
    }

    void Sprite::Init(wchar_t** texture, Color** color, Vector2D textureDimensions)
    {
        this->textureDimensions = new Vector2D(textureDimensions);

        Load2DTexture(texture);
        Load2DColor(color);
    }

    void Sprite::Load2DTexture(wchar_t** texture)
    {
        if (texture == nullptr)
        {
            this->texture = new wchar_t*[textureDimensions->y];
            for (int y = 0; y < textureDimensions->y; ++y)
            {
                this->texture[y] = new wchar_t[textureDimensions->x];
                for (int x = 0; x < textureDimensions->x; ++x)
                {
                    this->texture[y][x] = ' ';
                }
            }
        }
        else
        {
            this->texture = texture;
        }
    }

    void Sprite::Load2DColor(Color** color)
    {
        if (color == nullptr)
        {
            this->color = new Color*[textureDimensions->y];
            for (int y = 0; y < textureDimensions->y; ++y)
            {
                this->color[y] = new Color[textureDimensions->x];
                for (int x = 0; x < textureDimensions->x; ++x)
                {
                    this->color[y][x] = Color::WHT;
                }
            }
        }
        else
        {
            this->color = color;
        }
    }

    void Sprite::Load2DTextureAndColor(wchar_t** texture, Color** color)
    {
        Load2DTexture(texture);
        Load2DColor(color);
    }
} // Engine
