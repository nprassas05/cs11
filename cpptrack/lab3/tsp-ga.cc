#include "tsp-ga.hh"
#include "Point.hh"
#include <vector>

/* Constructor */
TSPGenome::TSPGenome(int numPoints) {
	circuitLength = 1e9;
}

/* constructor */
TSPGenome::TSPGenome(const std::vector<int> &order) {
	this->order = order;
	circuitLength = 1e9;
}

std::vector<int> TSPGenome::getOrder() const {
	return order;
}

void TSPGenome::computeCircuitLength(const std::vector<Point> points) {
	circuitLength = 90; ////////////////
}

double TSPGenome::getCircuitLength() const {
	return circuitLength;
}

TSPGenome findAShortPath(const std::vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations) {
	return TSPGenome(4); ///////////////
}