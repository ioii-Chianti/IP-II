#include <iostream>
#include <math.h>
#include "function.h"
using namespace std;

namespace oj {   // continue namespace oj

Triangle::Triangle(double edge1, double edge2, double edge3) {
    this->edge1 = edge1, this->edge2 = edge2, this->edge3 = edge3;
    if (edge1 > 0 && edge2 > 0 && edge3 > 0 && \
       edge1 + edge2 > edge3 && edge1 + edge3 > edge2 && edge2 + edge3 > edge1) {
        double s = (edge1 + edge2 + edge3) / 2;
        double area = sqrt(s * (s - edge1) * (s - edge2) * (s - edge3));
        setArea(area);
        setPerimeter(edge1 + edge2 + edge3);
    } else
        setArea(0), setPerimeter(0);
}

Rectangle::Rectangle(double width, double height) {
    this->width = width, this->height = height;
    if (width > 0 && height > 0) {
        setArea(width * height);
        setPerimeter((width + height) * 2);
    } else
        setArea(0), setPerimeter(0);
}

Circle::Circle(double radius, double pi) {
    this->radius = radius, this->pi = pi;
    if (radius > 0 && pi > 0) {
        setArea(pi * radius * radius);
        setPerimeter(2 * pi * radius);
    } else
        setArea(0), setPerimeter(0);
}

}   // end namespace oj