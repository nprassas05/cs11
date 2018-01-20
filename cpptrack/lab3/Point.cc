#include "Point.hh"
#include "lib/contracts.hh"
#include <iostream>
#include <cmath>

// Default constructor:  initializes the point to (0, 0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

// Initializes the point to (x, y, z).
Point::Point(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
	z_coord = val;
}

// Accessors:

double Point::getX() const {
  return x_coord;
}

double Point::getY() const {
  return y_coord;
}

double Point::getZ() const {
	return z_coord;
}

/* return the distance to another point */
double Point::distanceTo(const Point &p) const {
	PRE_COND(p != nullptr);
	double xDiff = x_coord - p.x_coord;
	double yDiff = y_coord - p.y_coord;
	double zDiff = z_coord - p.z_coord;
	return sqrt(
		(xDiff * xDiff) + 
		(yDiff * yDiff) + 
		(zDiff * zDiff)
	);
}

std::ostream& operator<<(std::ostream& out, Point& p) {
	out << "Point: (" << p.x_coord << ", " << p.y_coord
	    << ", " << p.z_coord << ")";
	return out;
}