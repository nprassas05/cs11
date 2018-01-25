#ifndef TSP_GENOME_H
#define TSP_GENOME_H

#include "Point.hh"
#include <vector>
#include <iostream>

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
	bool operator==(const TSPGenome& g);
	bool operator!=(const TSPGenome& g);
	friend std::ostream &operator<<(std::ostream &os, const TSPGenome &g);
};

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);

TSPGenome findAShortPath(const std::vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations);

bool shorterPath(const TSPGenome &, const TSPGenome &);

template<class T>
void myswap(std::vector<T> &, int, int);

void setRandomIndexes(int &, int &, int, int);
#endif