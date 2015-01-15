#include "level0.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"

using namespace std;

Level0::Level0() {
	winScore = 200;
	lockedSquares = 0;
}
// current colourList position is 0

Square* Level0::createSquare() {
	// create a BasicSquare with a colour chosen based on the given sequence file
	int colour;
	if (currentVPos >= colourList.size()) {
		currentVPos = 0; // go back to the start of the list if you reach the end
	}
	colour = colourList[currentVPos] - '0';
	currentVPos++;
	return new BasicSquare(colour, 0, 0);
} // end of createSquare()

Square* Level0::createSquare(int row, int column) {
	// create a BasicSquare with a colour chosen based on the given sequence file and given row/column
	int colour;
	if (currentVPos >= colourList.size()) {
		currentVPos = 0; // go back to the start of the list if you reach the end
	}
	colour = colourList[currentVPos] - '0';
	currentVPos++;
	return new BasicSquare(colour, row, column);
} // end of createSquare(int row, int column)

Square*** Level0::createGrid() {
	if (file != "no file") {
		return readFromFile();
	}
	else {
		setFileName("sequence.txt");
		return readFromFile();
	}
} // end of createGrid()