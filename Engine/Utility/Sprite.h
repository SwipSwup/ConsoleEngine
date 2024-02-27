//
// Created by david on 27/02/2024.
//

#ifndef SPRITE_H
#define SPRITE_H

namespace Engine
{
    struct Vector2D;

    struct Sprite
    {
    public:
        Sprite();
        Sprite(char** texureData, char*** colorData, Vector2D size);
        Sprite(char** data, Vector2D* size);
        ~Sprite();

    private:
        char** textureData;
        char*** colorData;


    public:
       const Vector2D* size;

        void LoadTextureData(char* data, Vector2D size);

        void LoadColorData(char*** data);

        void LoadTextureDataFromFile(char* path);

        void LoadColorDataFromFile(char* path);

        char* GetTextureAndColorData(int x, int y);
    };
} // Engine

#endif //SPRITE_H
