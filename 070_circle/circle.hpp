
#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point & init_center, double init_radius);
  void move(double dx, double dy);
  /* This method moves the circle's center by <dx,dy> (hint: Point already
     has a move method) */

  double intersectionArea(const Circle & otherCircle);
  /* This method computes the area of the intersection of this circle and
     otherCircle. 
     Note that if you lack the domain knowledge for this problem, you
     can (and should) find it on the internet before you begin the problem!
  */
};
