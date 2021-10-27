// header files for class Point
class Point {
 private:
  double x;
  double y;

 public:
  Point();
  void move(double dx, double dy);
  /* This method increases the point's x by dx, and its y by dy. */

  double distanceFrom(const Point & p);
  /* This func takes a constant reference to another point and computes 
     the distance between the two points. If you do not remember the
     formula for the distance between two points, you should be able to
     find this domain knowledge easily on the internet. */
};
