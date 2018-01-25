#include <iostream>
#include "tsp-ga.hh"
using namespace std;

inline void usage() {
	cout << "Usage: ./tsp-ga <population> <generations> <keepPercentage> <mutate>" << endl;
}

bool validArgs(int pop, int gen, double keep, int mutations) {
	if (pop < 0 || gen < 0 || keep < 0) return false;
	if (keep < 0 || keep > 1) return false;
	return true;
}

int main(int argc, char** argv) {
	if (argc != 5) {
		usage();
		return 1;
	}

	srand(time(0));
	int population;
	int generations;
	double keepPercentage;
	int numMutations;

	population = atoi(argv[1]);
	generations = atoi(argv[2]);
	keepPercentage = atof(argv[3]);
	numMutations = atoi(argv[4]);

	if (!validArgs(population, generations, keepPercentage, numMutations)) {
		usage();
		return 1;
	}

	/* Get the points from stdin and find the shortest traveling salesman path using
	   our new genetic algorithm. */
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
	cout << endl;

	int keep = (int) (keepPercentage * population);
	TSPGenome g = findAShortPath(points, population, generations, keep, numMutations);
	cout << "Shortest distance: " << g.getCircuitLength() << endl;
	return 0;
}