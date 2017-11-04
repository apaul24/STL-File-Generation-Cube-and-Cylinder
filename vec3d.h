/*
*  Author: Ahmed Paul
*  EE-553
*  STL File Generation: Cube and Cylinder
*/

#ifndef VEC3D_H
#define VEC3D_H

class Vec3d
{
    double m_x, m_y, m_z;

public:

    //Constructor
    Vec3d(double x=0, double y=0, double z=0) : m_x(x), m_y(y), m_z(z) {}

    //Print vector
    friend std::ostream& operator <<(std::ostream& s, const Vec3d &v);

    //Scalar Multiplication
    friend Vec3d operator *(const Vec3d &v, double c);
    friend Vec3d operator *(double c, const Vec3d &v);

    //Vector Addition
    friend Vec3d operator +(const Vec3d &v1, const Vec3d &v2);

    //Vector Subtraction
    friend Vec3d operator -(const Vec3d &v1, const Vec3d &v2);

    //Dot Product as function
    friend double dot(const Vec3d &v1, const Vec3d &v2);

    //Dot Product as method
    double dot(const Vec3d &v);

    //Distance as a function
    friend double dist(const Vec3d &v1, const Vec3d &v2);

    //Distance as a method
    double dist(const Vec3d &v);

    //Calculate normal of two vectors
    friend Vec3d calculateNormal(const Vec3d &u, const Vec3d &v);

    //Rotate vector
    Vec3d rotateVector(const double angle);

    //Member access methods
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }
};

#endif // VEC3D_H
