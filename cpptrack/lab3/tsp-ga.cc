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

/* accessors */
std::vector<int> TSPGenome::getOrder() const {
	return order;
}

double TSPGenome::getCircuitLength() const {
	return circuitLength;
}

/* compute the length of circuit, storing result internally in
   the genomes circuitLength field. */
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
	myswap(order, i, j);
}

/* return a new genome that is a combination of two parent genomes */
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2) {
	std::vector<int> order1 = g1.getOrder();
	std::vector<int> order2 = g2.getOrder();
	PRE_COND(order1.size() == order2.size());

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
		if (added.find(order2[i]) == added.end()) {
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
		for (size_t i = 0; i < populationSize; i++) {
			genomes[i].computeCircuitLength(points);
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
void myswap(std::vector<T> &v, int i, int j) {
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

/* Overloaded operators */
bool TSPGenome::operator==(const TSPGenome &g) {
	if (g.getOrder().size() != order.size()) return false;

	std::vector<int> gOrder = g.getOrder();
	for (int i = 0; i < gOrder.size(); i++) {
		if (order[i] != gOrder[i]) return false;
	}

	return true;
}

std::ostream &operator<<(std::ostream &os, const TSPGenome &g) {
	os << "Genome Order: ";
	for (const auto& x: g.order) {
		os << x << " ";
	}
	os << ": circuitLength is " << g.getCircuitLength();
	return os;
}

bool TSPGenome::operator!=(const TSPGenome &g) {
	return !(this->operator==(g));
}
