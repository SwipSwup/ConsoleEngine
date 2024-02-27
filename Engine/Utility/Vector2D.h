//
// Created by david on 24/02/2024.
//

#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace Engine {

struct Vector2D {
public:
    Vector2D(int x, int y);

    int x, y;

    static Vector2D zero;
};

} // Eninge

#endif //VECTOR2D_H
