#include "maze.hh"
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

/* constructors */
Maze::Maze(int rows, int cols) {
	int arrSize = (2 * rows + 1) * (2 * cols + 1);
	cells = new MazeCell[arrSize];
	numRows = rows;
	numCols = cols;
	start = Location(0, 0);
	end = Location(rows - 1, cols - 1);
}

// copy constructor
Maze::Maze(const Maze &m) {
	copyData(m);
}

/* destructor */
Maze::~Maze() {
	delete[] cells;
	cells = nullptr;
	assert(cells == nullptr);
}

// Maze assignment operator
Maze & Maze::operator=(const Maze &m) {
	// don't copying for self assignment
	if (&m != this) {
		copyData(m);
	}
	
	return *this;
}


// Returns the number of rows in the maze
int Maze::getNumRows() const {
	return numRows;
}

// Returns the number of columns in the maze
int Maze::getNumCols() const {
	return numCols;
}


// Returns the starting point in the maze
Location Maze::getStart() const {
	return start;
}

// Sets the starting point in the maze    
void Maze::setStart(int row, int col) {
	assert(0 <= row && row < numRows);
	assert(0 <= col && col < numCols);
	start.row = row;
	start.col = col;
}


// Returns the ending point in the maze    
Location Maze::getEnd() const {
	return end;
}

// Sets the ending point in the maze
void Maze::setEnd(int row, int col) {
	assert(0 <= row && row < numRows);
	assert(0 <= col && col < numCols);
	end.row = row;
	end.col = col;
}

// Sets all cells and walls to be empty, so that the maze is
// completely cleared
void Maze::clear() {
	int rows = expandedNumRows();
	int cols = expandedNumCols();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int k = i * cols + j;
			cells[k] = MazeCell::EMPTY;
		}
	}
}

// Places a wall at every location that can be a wall in the maze
void Maze::setAllWalls() {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			setWall(i, j, Direction::NORTH);
			setWall(i, j, Direction::WEST);
			if (j == numCols - 1) setWall(i, j, Direction::EAST);
			if (i == numRows - 1) setWall(i, j, Direction::SOUTH);
		}
	}
}


// Returns the value of the specified
MazeCell Maze::getCell(int cellRow, int cellCol) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	return cells[expandedIndex(cellRow, cellCol)];
}

void Maze::setCell(int cellRow, int cellCol, MazeCell val) {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	cells[expandedIndex(cellRow, cellCol)] = val;
}

// Returns the cell-coordinates of the neighboring cell in the specified
// direction.  Trips an assertion if the given cell has no neighbor in the
// specified direction (e.g. the NORTH neighbor of cell (0,5)).
Location Maze::getNeighborCell(int cellRow, int cellCol,
                         Direction direction) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	assert(!(cellRow == 0 && direction == Direction::NORTH));
	assert(!(cellRow == numRows - 1 && direction == Direction::SOUTH));
	assert(!(cellCol == 0 && direction == Direction::WEST));
	assert(!(cellCol == numCols - 1 && direction == Direction::EAST));

	Location neighbor = Location(cellRow, cellCol);
	if (direction == Direction::NORTH) {
		neighbor.row -= 1;
	} else if (direction == Direction::SOUTH) {
		neighbor.row += 1;
	} else if (direction == Direction::EAST) {
		neighbor.col += 1;
	} else if (direction == Direction::WEST) {
		neighbor.col -= 1;
	} else assert(false);

	return neighbor;
}

// Returns true if there is a wall in the specified direction from the
// given cell, false otherwise
bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	return cells[expandedWallIndex(cellRow, cellCol, direction)] == MazeCell::WALL;
}

// Puts a wall on the specified side of the given cell
void Maze::setWall(int cellRow, int cellCol, Direction direction) {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	cells[expandedWallIndex(cellRow, cellCol, direction)] = MazeCell::WALL;
}

// Removes a wall on the specified side of the given cell
void Maze::clearWall(int cellRow, int cellCol, Direction direction) {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	cells[expandedWallIndex(cellRow, cellCol, direction)] = MazeCell::EMPTY;
}


// Returns true if the specified maze cell has been visited.
bool Maze::isVisited(int cellRow, int cellCol) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	return getCell(cellRow, cellCol) == MazeCell::VISITED;
}

// Changes the cell's value to VISITED
void Maze::setVisited(int cellRow, int cellCol) {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	setCell(cellRow, cellCol, MazeCell::VISITED);
}

// Outputs the maze using simple ASCII-art to the specified output stream.
// The output format is as follows, using the example maze from the
// assignment write-up.  (The text to the right of the maze is purely
// explanatory, and you don't need to output it.)
//
// 3 4                 (# of rows and then # of columns)
// +---+---+---+---+   (each cell is 3 spaces wide, with a + at each corner)
// | S     |       |   (walls indicated by --- or |)
// +---+   +   +   +   (start indicated by S, end indicated by E)
// |   |   |   |   |
// +   +   +   +   +
// |           | E |
// +---+---+---+---+
void Maze::print(ostream &os) const {
	os << numRows << " " << numCols << endl;

	for (int i = 0; i < numRows; i++) {
		// output walls above row j
		for (int j = 0; j < numCols; j++) {
			os << "+";
			if (hasWall(i, j, Direction::NORTH)) {
				os << "---";
			} else {
				os << "   ";
			}
		}

		os << "+" << endl;

		for (int j = 0; j < numCols; j++) {
			if (hasWall(i, j, Direction::WEST)) {
				os << "|";
			} else {
				os << " ";
			}
			os << " ";

			if (start.row == i && start.col == j) {
				os << "S";
			} else if (end.row == i && end.col == j) {
				os << "E";
			} else {
				os << " ";
			}

			os << " ";

			if (j == numCols - 1 && hasWall(i, j, Direction::EAST)) {
				os << "|";
			}
		}

		os << endl;
	}

	int lastRow = numRows - 1;
	for (int j = 0; j < numCols; j++) {
		os << "+";
		if (hasWall(lastRow, j, Direction::SOUTH)) {
			os << "---";
		} else {
			os << "   ";
		}
	}
	os << "+" << endl;
}

int Maze::expandedIndex(int cellRow, int cellCol) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	return getArrayIndex(getCellArrayCoord(cellRow, cellCol));
}

int Maze::expandedWallIndex(int cellRow, int cellCol, Direction dir) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	return getArrayIndex(getWallArrayCoord(cellRow, cellCol, dir));
}

// Take 2D expanded coordinates and compute the corresponding 1D array index
int Maze::getArrayIndex(const Location &loc) const {
	assert(0 <= loc.row && loc.row < expandedNumRows());
	assert(0 <= loc.col && loc.col < expandedNumCols());
	return loc.row * expandedNumCols() + loc.col;
}

// Returns the expanded coordinates of the specified cell coordinates
Location Maze::getCellArrayCoord(int cellRow, int cellCol) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	return Location(cellRow * 2 + 1, cellCol * 2 + 1);
}

// Returns the expanded coordinates of the wall on a specific side of
// a cell given in cell coordinates
Location Maze::getWallArrayCoord(int cellRow, int cellCol, 
								 Direction dir) const {
	assert(0 <= cellRow && cellRow < numRows);
	assert(0 <= cellCol && cellCol < numCols);
	Location wall = getCellArrayCoord(cellRow, cellCol);
	switch (dir) {
		case Direction::NORTH:
			wall.row -= 1;
			break;
		case Direction::SOUTH:
			wall.row += 1;
			break;
		case Direction::EAST:
			wall.col += 1;
			break;
		case Direction::WEST:
			wall.col -= 1;
			break;
		default:
			assert(false);
	}

	return wall;
}

inline int Maze::expandedNumRows() const {
	return numRows * 2 + 1;
}

inline int Maze::expandedNumCols() const {
	return numCols * 2 + 1;
}

/* copy all the data of another maze; used for copy constructor
   and assignment operator. */
void Maze::copyData(const Maze &m) {
	numRows = m.getNumRows();
	numCols = m.getNumCols();

	if (cells != nullptr) {
		delete[]  cells;
	}

	int arrSize = (2 * numRows + 1) * (2 * numCols + 1);
	cells = new MazeCell[arrSize];

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			MazeCell mcell = m.getCell(i, j);
			setCell(i, j, mcell);

			if (m.hasWall(i, j, Direction::NORTH)) {
				setWall(i, j, Direction::NORTH);
			}

			if (m.hasWall(i, j, Direction::WEST)) {
				setWall(i, j, Direction::WEST);
			}

			if (i == numRows - 1 && m.hasWall(i, j, Direction::SOUTH)) {
				setWall(i, j, Direction::SOUTH);
			}

			if (j == numCols - 1 && m.hasWall(i, j, Direction::EAST)) {
				setWall(i, j, Direction::EAST);
			}
		}
	}

	// copy the start and end locations of the maze
	Location mStart = m.getStart();
	Location mEnd = m.getEnd();
	start.row = mStart.row;
	start.col = mStart.col;
	end.row = mEnd.row;
	end.col = mEnd.col;
}