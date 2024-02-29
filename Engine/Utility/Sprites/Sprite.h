//
// Created by david on 27/02/2024.
//

#ifndef SPRITE_H
#define SPRITE_H

namespace Engine
{
    struct Color;
    struct Vector2D;

    struct Sprite
    {
    public:
        Sprite(char** texture, Vector2D textureDimensions);
        Sprite(char** texture, Color** color, Vector2D textureDimensions);
        ~Sprite();

        char** texture;
        Color** color;
        Vector2D* textureDimensions;

    private:
        void Init(char** texture, Color** color, Vector2D textureDimensions);

    public:
        void Load2DTexture(char** texture);

        void Load2DColor(Color** color);

        void Load2DTextureAndColor(char** texture, Color** color);

    private:
    };
} // Engine

#endif //SPRITE_H
