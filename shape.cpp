/*
*  Author: Ahmed Paul
*  EE-553
*  STL File Generation: Cube and Cylinder
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "shape.h"

using namespace std;

/********* Functions for class: Triangle **********/

Triangle::Triangle(Vec3d v1, Vec3d v2, Vec3d v3)
    : m_vertex1(v1), m_vertex2(v2), m_vertex3(v3)
{
    //Calculate normal vector of triangle with normal facing outwards
    //u = vertex2 - vertex1, v = vertex3 - vertex1
    m_normal = calculateNormal(Vec3d(v2.getX() - v1.getX(), v2.getY() - v1.getY(), v2.getZ() - v1.getZ()),
                               Vec3d(v3.getX() - v1.getX(), v3.getY() - v1.getY(), v3.getZ() - v1.getZ()));
}

/********* Functions for class: Cube **********/

//Constructor (initialize facets based off of cube location and size)
Cube::Cube(double x, double y, double z, double size)
    : Shape(x,y,z), m_size(size)
{
    //Initiallize facets for cube
    Triangle t1(Vec3d(x,y+size,z+size), Vec3d(x+size,y,z+size), Vec3d(x+size,y+size,z+size));
    m_facets[0] = t1;

    Triangle t2(Vec3d(x+size,y,z+size), Vec3d(x,y+size,z+size), Vec3d(x,y,z+size));
    m_facets[1] = t2;

    Triangle t3(Vec3d(x,y,z), Vec3d(x+size,y+size,z), Vec3d(x+size,y,z));
    m_facets[2] = t3;

    Triangle t4(Vec3d(x+size,y+size,z), Vec3d(x,y,z), Vec3d(x,y+size,z));
    m_facets[3] = t4;

    Triangle t5(Vec3d(x,y,z), Vec3d(x+size,y,z+size), Vec3d(x,y,z+size));
    m_facets[4] = t5;

    Triangle t6(Vec3d(x+size,y,z+size), Vec3d(x,y,z), Vec3d(x+size,y,z));
    m_facets[5] = t6;

    Triangle t7(Vec3d(x+size,y,z+size), Vec3d(x+size,y+size,z), Vec3d(x+size,y+size,z+size));
    m_facets[6] = t7;

    Triangle t8(Vec3d(x+size,y+size,z), Vec3d(x+size,y,z+size), Vec3d(x+size,y,z));
    m_facets[7] = t8;

    Triangle t9(Vec3d(x+size,y+size,z), Vec3d(x,y+size,z+size), Vec3d(x+size,y+size,z+size));
    m_facets[8] = t9;

    Triangle t10(Vec3d(x,y+size,z+size), Vec3d(x+size,y+size,z), Vec3d(x,y+size,z));
    m_facets[9] = t10;

    Triangle t11(Vec3d(x,y,z), Vec3d(x,y+size,z+size), Vec3d(x,y+size,z));
    m_facets[10] = t11;

    Triangle t12(Vec3d(x,y+size,z+size), Vec3d(x,y,z), Vec3d(x,y,z+size));
    m_facets[11] = t12;
}

//Write STL description for cube
void Cube::writeShape(ofstream &f) const
{
    for(int i = 0; i < 12; ++i)
    {
        f << "facet normal " << m_facets[i].getNormal().getX() << " " << m_facets[i].getNormal().getY()
          << " " << m_facets[i].getNormal().getZ() << '\n';

        f << "\touter loop\n";

        f << "\t\tvertex " << m_facets[i].getVertex1().getX() << " " << m_facets[i].getVertex1().getY()
          << " " << m_facets[i].getVertex1().getZ() << '\n';

        f << "\t\tvertex " << m_facets[i].getVertex2().getX() << " " << m_facets[i].getVertex2().getY()
          << " " << m_facets[i].getVertex2().getZ() << '\n';

        f << "\t\tvertex " << m_facets[i].getVertex3().getX() << " " << m_facets[i].getVertex3().getY()
          << " " << m_facets[i].getVertex3().getZ() << '\n';

        f << "\tendloop\n";

        f << "endfacet\n";
    }
}

/********* Functions for class: Cylinder **********/

//Constructor (initialize facets based off of cylinder location, radius, and height)
Cylinder::Cylinder(double x, double y, double z, double r, double h, int numOfFacets)
    : Shape(x,y,z), m_r(r), m_h(h), m_numOfFacets(numOfFacets)
{
    //Create vector containing all vertices
    vector<Vec3d> vertices;
    vertices.reserve(2*numOfFacets);

    //Initialize first two points
    vertices.push_back(Vec3d(r+x,0+y,0+z));
    vertices.push_back(Vec3d(r+x,0+y,h+z));

    //Rotate point by angle to get new point
    Vec3d v(r, 0);

    for(int i = 1; i < 2*numOfFacets; ++i)
    {
        v = v.rotateVector(360/numOfFacets);
        vertices.push_back(Vec3d(v.getX()+x, v.getY()+y, z));
        vertices.push_back(Vec3d(v.getX()+x, v.getY()+y, h+z));
    }

    //Initialize facets for cylinder ring
    m_facets.reserve(4*numOfFacets);

    for(int i = 0, vertexIndex = 0; i < numOfFacets; ++i, vertexIndex += 2)
    {
       m_facets.push_back(Triangle(vertices[vertexIndex],
                                   vertices[vertexIndex+3],
                                   vertices[vertexIndex+1]));
    }

    for(int i = 0, vertexIndex = 0; i < numOfFacets; ++i, vertexIndex += 2)
    {
       m_facets.push_back(Triangle(vertices[vertexIndex],
                                   vertices[vertexIndex+2],
                                   vertices[vertexIndex+3]));
    }

    //Initialize facets for cylinder top and bottom faces
    for(int i = 0, vertexIndex = 0; i < numOfFacets; ++i, vertexIndex += 2)
    {
        if(i < numOfFacets-1)
        {
            m_facets.push_back(Triangle(vertices[vertexIndex],
                                        Vec3d(x,y,z),
                                        vertices[vertexIndex+2]));
        }
        else if(i == numOfFacets-1)
        {
            m_facets.push_back(Triangle(vertices[vertexIndex],
                                        Vec3d(x,y,z),
                                        vertices[0]));
        }
    }

    for(int i = 0, vertexIndex = 1; i < numOfFacets; ++i, vertexIndex += 2)
    {
        if(i < numOfFacets-1)
        {
            m_facets.push_back(Triangle(vertices[vertexIndex],
                                        Vec3d(x,y,z+h),
                                        vertices[vertexIndex+2]));
        }
        else if(i == numOfFacets-1)
        {
            m_facets.push_back(Triangle(vertices[vertexIndex],
                                        Vec3d(x,y,z+h),
                                        vertices[1]));
        }
    }
}

//Write STL description for cylinder
void Cylinder::writeShape(ofstream &f) const
{
    for(unsigned int i = 0; i < m_facets.size(); ++i)
    {
        f << "facet normal " << m_facets[i].getNormal().getX() << " " << m_facets[i].getNormal().getY()
          << " " << m_facets[i].getNormal().getZ() << '\n';

        f << "\touter loop\n";

        f << "\t\tvertex " << m_facets[i].getVertex1().getX() << " " << m_facets[i].getVertex1().getY()
          << " " << m_facets[i].getVertex1().getZ() << '\n';

        f << "\t\tvertex " << m_facets[i].getVertex2().getX() << " " << m_facets[i].getVertex2().getY()
          << " " << m_facets[i].getVertex2().getZ() << '\n';

        f << "\t\tvertex " << m_facets[i].getVertex3().getX() << " " << m_facets[i].getVertex3().getY()
          << " " << m_facets[i].getVertex3().getZ() << '\n';

        f << "\tendloop\n";

        f << "endfacet\n";
    }
}


/********* Functions for class: CAD **********/

//Destructor
CAD::~CAD()
{
    for(unsigned int i = 0; i < m_shapes.size(); ++i)
        delete m_shapes[i];
}

//Write STL file
void CAD::write(const string fileName) const
{
    //Open STL file to write to
    ofstream stlFile(fileName);

    //Check if file cannot be opened
    if (!stlFile)
    {
        cerr << "Error. " << fileName << " could not be opened." << "\n";
        exit(1);
    }

    //Write STL descriptions for shapes in shape list 'm_shapes'
    stlFile << "solid shapes\n";

    for(unsigned int i = 0; i < m_shapes.size(); ++i)
        m_shapes[i]->writeShape(stlFile);

    stlFile << "endsolid shapes";
}

//Add cube to shape list
void CAD::add(Cube *cube)
{
    m_shapes.push_back(cube);
}

//Add cylinder to shape list
void CAD::add(Cylinder *cyl)
{
    m_shapes.push_back(cyl);
}
