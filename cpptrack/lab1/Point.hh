#include <iostream>

// A 3-dimensional point class
// Coordinates are double-precision floating point.
class Point {

private:
  double x_coord;
  double y_coord;
  double z_coord;

public:
  // Constructors
  Point();                      // default constructor
  Point(double x, double y, double z);    // two-argument constructor

  // Destructor
  ~Point();

  // Mutator methods
  void setX(double val);
  void setY(double val);
  void setZ(double val);

  // Accessor methods
  double getX();
  double getY();
  double getZ();

  // distance to another point
  double distanceTo(const Point&) const;

  friend std::ostream& operator<<(std::ostream& out, Point& p);
};
