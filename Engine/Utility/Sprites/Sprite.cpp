//
// Created by david on 27/02/2024.
//

#include "Sprite.h"
#include "../Vector2D.h"

namespace Engine
{
    Sprite::Sprite(char** texture, Vector2D textureDimensions)
    {
        Init(texture, nullptr, textureDimensions);
    }

    Sprite::Sprite(char** texture, Color** color, Vector2D textureDimensions)
    {
        Init(texture, color, textureDimensions);
    }

    Sprite::~Sprite()
    {
        delete textureDimensions;
    }

    void Sprite::Init(char** texture, Color** color, Vector2D textureDimensions)
    {
        this->texture = texture;
        this->color = color;
        this->textureDimensions = new Vector2D(textureDimensions);
    }

    void Sprite::Load2DTexture(char** texture)
    {
        this->texture = texture;
    }

    void Sprite::Load2DColor(Color** color)
    {
        this->color = color;
    }

    void Sprite::Load2DTextureAndColor(char** texture, Color** color)
    {
        Load2DTexture(texture);
        Load2DColor(color);
    }
} // Engine
