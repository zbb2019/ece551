#include "circle.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
Circle::Circle(Point & init_center, double init_radius) :
    center(init_center),
    radius(init_radius) {
}

void Circle::move(double dx, double dy) {
  /* This method moves the circle's center by <dx,dy> (hint: Point already
     has a move method) */
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  /* This method computes the area of the intersection of this circle and
     otherCircle. 
     Note that if you lack the domain knowledge for this problem, you
     can (and should) find it on the internet before you begin the problem!
  */
  double d = center.distanceFrom(otherCircle.center);
  if (d < radius + otherCircle.radius) {
    if (d <= std::abs(radius - otherCircle.radius)) {
      return M_PI * std::min(std::pow(radius, 2), std::pow(otherCircle.radius, 2));
    }
    double d1 = (std::pow(radius, 2) - std::pow(otherCircle.radius, 2) + std::pow(d, 2)) /
                (2 * d);
    double d2 = d - d1;
    double interArea =
        std::pow(radius, 2) * std::acos(d1 / radius) -
        d1 * std::sqrt(std::pow(radius, 2) - std::pow(d1, 2)) +
        std::pow(otherCircle.radius, 2) * std::acos(d2 / otherCircle.radius) -
        d2 * std::sqrt(std::pow(otherCircle.radius, 2) - std::pow(d2, 2));
    return interArea;
  }
  return 0;
}
