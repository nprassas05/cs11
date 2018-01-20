#ifndef TSP_GENOME_H
#define TSP_GENOME_H

#include "Point.hh"
#include <vector>

class TSPGenome {

private:
	std::vector<int> order;
	double circuitLength;

public:
	TSPGenome(int);
	TSPGenome(const std::vector<int> &order);
	std::vector<int> getOrder() const;
	void computeCircuitLength(const std::vector<Point> points);
	double getCircuitLength() const;
};

TSPGenome findAShortPath(const std::vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations);

#endif