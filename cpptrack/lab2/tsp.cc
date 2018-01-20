#include <iostream>
#include "Point.hh"
#include <algorithm>
#include <vector>
#include <string>
#include "lib/contracts.hh"
using namespace std;

/* Find the length of a cyclic path */
double circuitLength(const vector<Point> &, const vector<int>&);

/* find the order leading to the shortest path traveled
   in the traveleling salesman problem. */
vector<int> findShortestPath(const vector<Point> &);
string vectorAsString(const vector<int> &);

/* get a set of points from standard input and output
   the shortest Hamiltonian cycle that can be traversed
   using those points. */
int main() {
	int numPoints;
	double x, y, z;
	vector<Point> points;

	cout << "How many points? ";
	cin >> numPoints;
	points.resize(numPoints, Point());

	for (size_t i = 0; i < numPoints; i++) {
		cout << "Point " << i << ": ";
		cin >> x >> y >> z;
		points[i].setX(x);
		points[i].setY(y);
		points[i].setZ(z);
	}

	vector<int> bestOrder = findShortestPath(points);
	cout << "Best order: " << vectorAsString(bestOrder) << endl;
	cout << "Shortest Distance: " << circuitLength(points, bestOrder) << endl;

	return 0;
}

/* compute the total length of a path when the points are visited
   in the specified order vector. */
double circuitLength(const vector<Point> &points, const vector<int> &order) {
	PRE_COND(order.size() > 0 && order.size() == points.size());
	double dist = 0;
	size_t len = order.size();

	for (size_t i = 0; i < len; i++) {
		int j = order[i];
		int k = order[(i + 1) % len]; 
		dist += points[j].distanceTo(points[k]);
	}

	return dist;
}

/* Return a vector specifying the order in which to visit all
   points once and returning back to the starting points such
   that the total distance traveled is minimized */
vector<int> findShortestPath(const vector<Point> &points) {
	size_t len = points.size();
	vector<int> order(len);
	for (size_t i = 0; i < len; i++) {
		order[i] = i;
	}

	vector<int> shortestPathOrder = order;
	double shortestPathLen = circuitLength(points, order);

	while (next_permutation(order.begin(), order.end())) {
		double cLen = circuitLength(points, order);
		if (cLen < shortestPathLen) {
			shortestPathLen = cLen;
			shortestPathOrder = order;
		}
	}

	return shortestPathOrder;
}

/* Return a string representation of an integer vector */
string vectorAsString(const vector<int> &order) {
	string s = "[";
	vector<int>::const_iterator it;
	for (it = order.begin(); it != order.end(); it++) {
		s += to_string(*it) + " ";
	}
	s.erase(s.size() - 1, 1);
	s.append("]");
	return s;
}