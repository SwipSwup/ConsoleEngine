//
// Created by david on 29/02/2024.
//

#ifndef VECTOR3D_H
#define VECTOR3D_H

namespace Engine {

struct Vector3D {
    Vector3D(int x, int y, int z);

    int x, y, z;

    //Vector3D operator =(Vector3D);

    Vector3D operator+(Vector3D vector);
    Vector3D* operator+=(Vector3D vector);
};

} // Engine

#endif //VECTOR3D_H
