//
// Created by david on 24/02/2024.
//

#include "Vector2D.h"

namespace Engine
{
    Vector2D Vector2D::zero = Vector2D(0, 0);

    Vector2D::Vector2D(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
} // Eninge
