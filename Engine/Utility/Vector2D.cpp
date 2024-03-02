//
// Created by david on 24/02/2024.
//

#include "Vector2D.h"

#include <cmath>

namespace Engine
{
    Vector2D Vector2D::zero = Vector2D(0, 0);


    Vector2D::Vector2D(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    double Vector2D::Distance(Vector2D vec)
    {
        return std::sqrt(pow(x - vec.x, 2) + pow(y - vec.y, 2));
    }
} // Eninge
