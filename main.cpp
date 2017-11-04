/*
*  Author: Ahmed Paul
*  EE-553
*  STL File Generation: Cube and Cylinder
*/

#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include "shape.h"

using namespace std;

int main()
{
    CAD c;
    c.add(new Cube(0,0,0,5));
    c.add(new Cylinder(100,0,0,    3, 10, 10));
    c.write("Cube_and_Cylinder.stl");

    return 0;
}
