#include <iostream>
#include <cassert>
#include "Point.hh"
#include "tsp-ga.hh"
#include "lib/contracts.hh"
using namespace std;

void testA() {
	cout << "Test A" << endl;
	TSPGenome g(5);
	vector<int> o = g.getOrder();
	cout << "order vector: ";
	for (auto x: o) {
		cout << x << " ";
	} cout << endl;
	cout << "Circuit Length: " << g.getCircuitLength() << endl;

	TSPGenome g2({5, 4, 3, 2, 1, 0});
	for (auto &y: g2.getOrder()) {
		cout << y << " ";
	} cout << endl;
	cout << "Circuit Length: " << g2.getCircuitLength() << endl;

	vector<Point> points = {Point(1, 2, 3), Point(1, 2, 3), Point(1, 2, 3), 
							Point(1, 2, 3), Point(1, 2, 5)};
	TSPGenome g3({0, 1, 2, 3, 4});
	g3.computeCircuitLength(points);
	 // decimal precision of doubles aren't guaranteed to be exact
	assert(g3.getCircuitLength() - 4 <= 0.000001);
	cout << g3.getCircuitLength() << endl;
	cout << endl;
}


void testB() {
	cout << "Test B:" << endl;
	srand(time(0));
	TSPGenome g({0, 1, 2, 3, 4, 5});
	TSPGenome g2({0, 1, 2, 3, 4, 5,});
	// make sure overloarded == operator works
	assert(g == g2);

	g.mutate();
	assert(g != g2);
	cout << "After mutating: ";
	for (auto &x: g.getOrder()) {
		cout << x << " ";
	} cout << endl;
	cout << endl;
}

void testC() {
	cout << "Test C:" << endl;
	TSPGenome g1({0, 3, 2, 5, 4, 1});
	TSPGenome g2({5, 4, 3, 2, 1, 0});

	TSPGenome g3 = crosslink(g1, g2);
	cout << g1 << endl << g2 << endl << g3 << endl;
	cout << endl;
}

void testD() {
	cout << "Test D:" << endl;
	vector<Point> points = {
		Point(8, 9, 3), Point(4, 7, 8), Point(9, 2, 2),
		Point(1, 3, 0), Point(5, 0, 7), Point(5, 8, 0),
		Point(7, 4, 4), Point(4, 5, 0), Point(8, 1, 2),
		Point(7, 7, 4), Point(7, 9, 8), Point(5, 9, 9)
	};

	TSPGenome bestGenome = findAShortPath(points, 1000, 100, 400, 1);
	cout << bestGenome << endl;
}

void testE() {

}

void allTests() {
	testA();
	testB();
	testC();
	testD();
	testE();
	cout << "All test cases passed" << endl;
}

int main() {
	allTests();
	return 0;
}