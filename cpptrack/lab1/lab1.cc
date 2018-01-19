#include <iostream>
#include <cmath>
#include "Point.hh"
#include "lib/contracts.hh"
using namespace std;

/* Area within a triangle defined by 3 points */
double computeArea(const Point &, const Point &, const Point &);

const int NPOINTS = 3;

/* Request three points from user, and determine
   the area of a triangle enclosed by those three points.
   For now will not handle bad input. */
int main() {
	Point *points[3];
	double x, y, z;

	for (int i = 0; i < NPOINTS; i++) {
		cout << "Point " << (i + 1) << ": ";
		cin >> x >> y >> z;
		points[i] = new Point(x, y, z);
	}

	cout << "Area is: " << computeArea(*points[0], *points[1], *points[2])
	     << endl;
	return 0;
}

/* Computes the area within triangle defined by 3 points using
   Heron's formula */
double computeArea(const Point &a, const Point &b, const Point &c) {
	double sideA = a.distanceTo(b);
	double sideB = a.distanceTo(c);
	double sideC = b.distanceTo(c);

	double s = (sideA + sideB + sideC) / 2;
	return sqrt(
		s * (s - sideA) * (s - sideB) * (s - sideC)
	);
}