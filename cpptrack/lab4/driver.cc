#include "maze.hh"
#include <iostream>
#include <cassert>
using namespace std;

void testA() {
	Maze m(3, 4);
	cout << "Rows, Cols: " << m.getNumRows() << ", " << m.getNumCols() << endl;
	cout << "Expanded: " << m.expandedNumRows() << ", " << m.expandedNumCols() << endl;
	cout << "(0, 1) maps to " << m.expandedIndex(0, 1) << endl;
	cout << "(0, 0) maps to " << m.expandedIndex(0, 0) << endl;

	cout << "Exanded Wall Index next to (0, 0): " << m.expandedWallIndex(0, 0, Direction::NORTH)
	     << endl;

	m.setWall(0, 0, Direction::NORTH);
	assert(m.hasWall(0, 0, Direction::NORTH));
	m.clearWall(0, 0, Direction::NORTH);
	assert(!m.hasWall(0, 0, Direction::NORTH));
}

void testB() {
	Maze m(3, 4);
	m.setStart(0, 0);
	m.setEnd(2, 3);

	for (int j = 0; j < m.getNumCols(); j++) {
		m.setWall(0, j, Direction::NORTH);
		m.setWall(m.getNumRows() -1, j, Direction::SOUTH);
	}
	for (int i = 0; i < m.getNumRows(); i++) {
		m.setWall(i, 0, Direction::WEST);
		m.setWall(i, m.getNumCols() - 1, Direction::EAST);
	}

	m.setWall(0, 0, Direction::SOUTH);
	m.setWall(0, 1, Direction::EAST);
	m.setWall(1, 1, Direction::EAST);
	m.setWall(1, 1, Direction::WEST);
	m.setWall(1, 2, Direction::EAST);
	m.setWall(2, 3, Direction::WEST);

	m.print(cout);
}

int main() {
	//testA();
	testB();
	return 0;
}