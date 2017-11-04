/*
*  Author: Ahmed Paul
*  EE-553
*  STL File Generation: Cube and Cylinder
*/

using namespace std;
#include <iostream>
#include <cmath>
#include "vec3d.h"

/************ Functions *************/

//Print vector
ostream& operator <<(ostream& s, const Vec3d &v)
{
    s << "(" << v.m_x << ", " << v.m_y << ", " << v.m_z << ")";

    return s;
}

//Scalar Multiplication
Vec3d operator *(const Vec3d &v, double c)
{
    Vec3d result;

    result.m_x = v.m_x * c;
    result.m_y = v.m_y * c;
    result.m_z = v.m_z * c;

    return result;
}

//Vector Addition
Vec3d operator +(const Vec3d &v1, const Vec3d &v2)
{
    Vec3d result;

    result.m_x = v1.m_x + v2.m_x;
    result.m_y = v1.m_y + v2.m_y;
    result.m_z = v1.m_z + v2.m_z;

    return result;
}

//Vector Subtraction
Vec3d operator -(const Vec3d &v1, const Vec3d &v2)
{
    Vec3d result;

    result.m_x = v1.m_x - v2.m_x;
    result.m_y = v1.m_y - v2.m_y;
    result.m_z = v1.m_z - v2.m_z;

    return result;
}

//Dot Product as a function
double dot(const Vec3d &v1, const Vec3d &v2)
{
    return (v1.m_x*v2.m_x) + (v1.m_y*v2.m_y) + (v1.m_z*v2.m_z);
}

//Distance as a function
double dist(const Vec3d &v1, const Vec3d &v2)
{
    return sqrt( pow((v1.m_x-v2.m_x), 2) + pow((v1.m_y-v2.m_y), 2) + pow((v1.m_z-v2.m_z), 2) );
}

//Calculate normal of two vectors
Vec3d calculateNormal(const Vec3d &u, const Vec3d &v)
{
    //N = u x v
    Vec3d N((u.m_y*v.m_z) - (u.m_z*v.m_y),
            (u.m_z*v.m_x) - (u.m_x*v.m_z),
            (u.m_x*v.m_y) - (u.m_y*v.m_x));

    double mag = abs(N.m_x) + abs(N.m_y) + abs(N.m_z);

    //Normalize vector
    N.m_x /= mag;
    N.m_y /= mag;
    N.m_z /= mag;

    return N;
}

//Rotate vector by angle
Vec3d Vec3d::rotateVector(const double angle)
{
    const double PI = 3.14159265;

    double newX = (m_x*cos(angle*PI / 180)) - (m_y*sin(angle*PI / 180));
    double newY = (m_y*cos(angle*PI / 180)) + (m_x*sin(angle*PI / 180));

    return Vec3d(newX, newY);
}
