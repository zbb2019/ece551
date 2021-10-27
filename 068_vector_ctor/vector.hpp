/* write your class interface in this file
   write function definitions only if they are very short
 */

class Vector2D {
  double x;
  double y;

 public:
  Vector2D();
  Vector2D(double init_x, double init_y);

  double getMagnitude() const;
  /* This function returns the magnitude of the vector from the origin
     (0, 0) to (x, y). This is given by sqrt(x^2 + y^2). */

  Vector2D operator+(const Vector2D & rhs) const;
  /* The overloaded + operator should do vector addition in the usual
     way and return a copy of the new vector. */

  Vector2D & operator+=(const Vector2D & rhs);
  /* The overloaded += operator should add the lhs and rhs vector and
     assign the result to the object pointed to by this. */

  double dot(const Vector2D & rhs) const;
  /* This function performs the dot product operation, returning a double
     (x1*x2 + y1*y2) */

  void print() const;
  /* This function should print the vector in the format <%.2f, %.2f>,
     giving the x and y values. */
};
