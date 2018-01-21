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
	void mutate();
};

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);

TSPGenome findAShortPath(const std::vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations);

bool shorterPath(const TSPGenome &, const TSPGenome &);

template<class T>
void swap(std::vector<T>, size_t, size_t);

void setRandomIndexes(int &, int &, int, int);
#endif