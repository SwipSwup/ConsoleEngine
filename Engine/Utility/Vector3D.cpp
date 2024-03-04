//
// Created by david on 29/02/2024.
//

#include "Vector3D.h"

namespace Engine {
    Vector3D::Vector3D(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /*Vector3D Vector3D::operator=(Vector3D vector)
    {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;

        return this;
    }*/

    Vector3D Vector3D::operator+(Vector3D vector)
    {
        return {this->x + vector.x, this->y + vector.y, this->z + vector.z};
    }

    Vector3D* Vector3D::operator+=(Vector3D vector)
    {
        this->x += vector.x;
        this->y += vector.y;
        this->z += vector.z;

        return this;
    }
} // Engine