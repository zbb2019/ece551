#include "point.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>

Point::Point() : x(0), y(0) {
}
void Point::move(double dx, double dy) {
  /* This method increases the point's x by dx, and its y by dy. */
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  /* This func takes a constant reference to another point and computes 
     the distance between the two points. If you do not remember the
     formula for the distance between two points, you should be able to
     find this domain knowledge easily on the internet. */
  return std::sqrt(std::pow((x - p.x), 2) + std::pow((y - p.y), 2));
}
