#include <iostream>
#include <cassert>
#include "Point.hh"
using namespace std;

/**

g++ tests.cc Point.cc && ./a.out

**/

void testA() {
	Point p1(1, 1, 1);
	Point p2(1, 1, 1);
	assert(p1.distanceTo(p2) == 0);
	cout << p1.distanceTo(p2) << endl;
}

void testB() {
	Point p1(1, 2, 3);
	Point p2(1, 2, 7);
	double d = p1.distanceTo(p2);
	assert(d == 4);
	cout << p1 << endl << p2 << endl;
}

int main() {
	testA();
	testB();
	cout << "All tests passed" << endl;
	return 0;
}