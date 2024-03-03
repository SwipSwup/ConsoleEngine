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
        Sprite(wchar_t** texture, Vector2D textureDimensions);
        Sprite(wchar_t** texture, Color** color, Vector2D textureDimensions);
        ~Sprite();

        Vector2D* textureDimensions;
        wchar_t** texture;
        Color** color;

    private:
        void Init(wchar_t** texture, Color** color, Vector2D textureDimensions);


    public:
        void Load2DTexture(wchar_t** texture);

        void Load2DColor(Color** color);

        void Load2DTextureAndColor(wchar_t** texture, Color** color);
    private:
    };
} // Engine

#endif //SPRITE_H
