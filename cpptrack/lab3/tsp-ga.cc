#include "tsp-ga.hh"
#include "Point.hh"
#include "lib/contracts.hh"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <cstdlib>

/* Constructors */
TSPGenome::TSPGenome(int numPoints) {
	order.resize(numPoints);
	for (size_t i = 0; i < numPoints; i++) {
		order[i] = i;
	}
	random_shuffle(order.begin(), order.end());
	circuitLength = 1e9;
}

TSPGenome::TSPGenome(const std::vector<int> &order) {
	this->order = order;
	circuitLength = 1e9;
}

/* accessor */
std::vector<int> TSPGenome::getOrder() const {
	return order;
}

void TSPGenome::computeCircuitLength(const std::vector<Point> points) {
	double dist = 0;
	size_t len = order.size();

	for (size_t i = 0; i < len; i++) {
		int j = order[i];
		int k = order[(i + 1) % len]; 
		dist += points[j].distanceTo(points[k]);
	}

	circuitLength = dist;
}

/* Swap the contents of two randomly chosen elements in the
   order vector. */
void TSPGenome::mutate() {
	int i, j;
	setRandomIndexes(i, j, 0, order.size());
	swap(order, i, j);
	// int i = rand() % order.size();
	// int j = rand() % order.size();
	// while (j == i) {
	// 	j = rand() % order.size();
	// }
	// int temp = order[i];
	// order[i] = order[j];
	// order[j] = temp;
}

double TSPGenome::getCircuitLength() const {
	return circuitLength;
}

/* return a new genome that is a combination of two parent genomes */
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2) {
	PRE_COND(g1.getOrder().size() == g2.getOrder().size());

	std::vector<int> order1 = g1.getOrder();
	std::vector<int> order2 = g2.getOrder();
	size_t len = g1.getOrder().size();

	
	std::vector<int> offspringOrder(len);
	int index = rand() % len;
	std::set<int> added;

	for (size_t i = 0; i < index; i++) {
		offspringOrder[i] = order1[i];
		added.insert(order1[i]);
	}

	for (size_t i = 0; i < len; i++) {
		INVARIANT(index < len);
		if (added.find(order2[i]) != added.end()) {
			offspringOrder[index] = order2[i];
			index = index + 1;
			added.insert(order2[i]);
		}
	}

	ASSERT(index == len);
	return TSPGenome(offspringOrder);
}

/* find a path that is shortest among the generations made using
   a genetic algorithm.  The path returned is not guaranteed to be
   the shortest path, but should be path that is "pretty good". */
TSPGenome findAShortPath(const std::vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations) {

	/* generate initial population of random genomes, and also
	   have each newly created genome calculate the circuit length
	   based on its given order. */
	std::vector<TSPGenome> genomes;
	for (size_t i = 0; i < populationSize; i++) {
		TSPGenome t(points.size());
		genomes.push_back(t);
	}

	for (int gen = 0; gen < numGenerations; gen++) {
		for (TSPGenome g: genomes) {
			g.computeCircuitLength(points);
		}

		sort(genomes.begin(), genomes.end(), shorterPath);
		if (gen % 10 == 0) {
			std::cout << "Generation " << gen << ": shortest path is "
			     << genomes[0].getCircuitLength() << std::endl;
		}

		for (size_t i = keepPopulation; i < populationSize; i++) {
			int j, k;
			setRandomIndexes(j, k, 0, keepPopulation);
			genomes[i] = crosslink(genomes[j], genomes[k]);
		}

		/* randomly mutate the genome vector, exluding the first element
		   with the shortest path so far. */
		for (size_t i = 0; i < numMutations; i++) {
			int index = 1 + rand() % (populationSize - 1);
			genomes[index].mutate();
		}

	}
	
	/* return the genome with the shortest path among all generations */
	return genomes[0];
}

/* comparison function used for sorting genomes based on
   their circuit lengths */
bool shorterPath(const TSPGenome &g1, const TSPGenome &g2) {
	return g1.getCircuitLength() < g2.getCircuitLength();
}

/* generic swap function for a vector */
template<class T>
void swap(std::vector<T> v, size_t i, size_t j) {
	PRE_COND(0 <= i && i < v.size());
	PRE_COND(0 <= j && j < v.size());
	T temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* set integers j and k to two different random integers
   in the range [lower, upper) */
void setRandomIndexes(int& j, int& k, int lower, int upper) {
	j = lower + (rand() % (upper - lower));
	k = lower + (rand() % (upper - lower));

	while (k == j) {
		k = lower + (rand() % (upper - lower));
	}
}
