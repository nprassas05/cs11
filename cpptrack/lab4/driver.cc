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
	Maze m1(4, 6);
    m1.clear();
    
    m1.setCell(2, 2, MazeCell::VISITED);
    m1.setWall(1, 3, Direction::EAST);
    m1.setCell(3, 5, MazeCell::VISITED);
    m1.setWall(3, 4, Direction::SOUTH);

    Maze m2(m1);
}

int main() {
	testA();
	testB();
	return 0;
}