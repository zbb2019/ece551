#include "vector.hpp"

#include <cmath>
#include <cstdio>
/* write your class implementation in this file
 */

Vector2D::Vector2D() : x(0), y(0) {
}

Vector2D::Vector2D(double init_x, double init_y) : x(init_x), y(init_y) {
  /* This function initializes x and y to be the arguments passed in. */
}

double Vector2D::getMagnitude() const {
  /* This function returns the magnitude of the vector from the origin
       (0, 0) to (x, y). This is given by sqrt(x^2 + y^2), for which you
       will likely want to use functions in cmath. (Note that when you
       include cmath, instead of math.h, it puts functions in the std
       namespace, so you must use the fully qualified name std::sqrt.)
       Think about why this method should be const. */
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  /* The overloaded + operator should do vector addition in the usual
       way and return a copy of the new vector. Think about why the 
       parameter should be const. */
  Vector2D ans;
  ans.x = x + rhs.x;
  ans.y = y + rhs.y;
  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  /* The overloaded += operator should add the lhs and rhs vector and
       assign the result to the object pointed to by this. */
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  /* This function performs the dot product operation, returning a double
    x1*x2 + y1*y2. */
  return x * rhs.x + y * rhs.y;
}

void Vector2D::print() const {
  /* This function should print the vector in the format <%.2f, %.2f>,
       giving the x and y values. */
  std::printf("<%.2f, %.2f>", x, y);
}
