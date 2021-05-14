#include <iostream>
#include "function.h"
using namespace std;

namespace oj {

Sphere::Sphere(double radius, double pi) {
    this->radius = radius, this->pi = pi;
    if (radius > 0 && pi > 0)
        setVolume(4.0 / 3.0 * pi * radius * radius * radius);
    else
        setVolume(0);
}

Cone::Cone(double radius, double height, double pi) {
    this->radius = radius, this->height = height, this->pi = pi;
    if (radius > 0 && height > 0 && pi > 0)
        setVolume(pi * radius * radius * height / 3);
    else
        setVolume(0);
}

Cuboid::Cuboid(double length, double width, double height) {
    this->length = length, this->width = width, this->height = height;
    if (length > 0 && width > 0 && height > 0)
        setVolume(length * width * height);
    else
        setVolume(0);
}

Cube::Cube(double side) : Cuboid(side, side, side) {}

}   // end namespace oj