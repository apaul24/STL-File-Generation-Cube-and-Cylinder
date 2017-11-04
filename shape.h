/*
*  Author: Ahmed Paul
*  EE-553
*  STL File Generation: Cube and Cylinder
*/

#ifndef SHAPE_H
#define SHAPE_H

#include "vec3d.h"

/***** Triangle *****/
class Triangle
{
    Vec3d m_vertex1;
    Vec3d m_vertex2;
    Vec3d m_vertex3;
    Vec3d m_normal;

public:
    //Constructors
    Triangle() {}
    Triangle(Vec3d v1, Vec3d v2, Vec3d v3);

    //Destructor
    ~Triangle() {}

    //Member access methods
    Vec3d getVertex1() const { return m_vertex1; }
    Vec3d getVertex2() const { return m_vertex2; }
    Vec3d getVertex3() const { return m_vertex3; }
    Vec3d getNormal() const { return m_normal; }
};

/***** Shape *****/
class Shape
{
    double m_x, m_y, m_z;

public:
    //Constructor
    Shape(double x, double y, double z)
        : m_x(x), m_y(y), m_z(z) {}

    //Write shape STL description
    virtual void writeShape(std::ofstream &f) const = 0;

    //Destructor
    virtual ~Shape(){}
};

/***** Cylinder *****/
class Cylinder : public Shape
{
    double m_r, m_h;
    int m_numOfFacets;
    std::vector<Triangle> m_facets;

public:
    //Constructor
    Cylinder(double x, double y, double z, double r, double h, int numOfFacets);

    //Write STL description for cylinder
    virtual void writeShape(std::ofstream &f) const;

    //Destructor
    virtual ~Cylinder() {}
};

/***** Cube *****/
class Cube: public Shape
{
    double m_size;
    Triangle m_facets[12];

public:
    //Constructor
    Cube(double x, double y, double z, double size);

    //Write STL description for cube
    virtual void writeShape(std::ofstream &f) const;

    //Destructor
    virtual ~Cube() {}
};

class CAD
{
    std::vector<Shape*> m_shapes;

public:
    //Constructor
    CAD() {}

    //Deallocate memory allocated for shapes
    ~CAD();

    //Add cube to shape list
    void add(Cube *c);

    //Add cylinder to shape list
    void add(Cylinder *c);

    //Write STL file
    void write(const std::string fileName) const;
};

#endif // SHAPE_H
