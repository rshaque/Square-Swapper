#include "board.h"
#include "lateralsquare.h"
#include "match_horizontal.h"
#include "match_vertical.h"
#include "match_L.h"
#include "window.h"
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

Board::Board(string fileName, int lvlNum, bool textOnly, string colourScheme){
	score = 0;
	winScore = 0;
	level = lvlNum;
	movesRemaining = 10;
	lvl = NULL;
	if (!textOnly){
		window = new Xwindow(500, 500, colourScheme);	
	} else {
		window = NULL;
	}
	#ifdef DEBUG
	cout << "set level to 0" << endl;
	#endif
	this->fileName = fileName;
	initBoard();
}

void Board::setTextOnly(bool textOnly){
	this->textOnly = textOnly;
}

Board::~Board(){
	/*
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			delete grid[i][j];
		}
	}
	for (int i = 0; i < 10; i++){
		delete[] grid[i];
	}
	delete[] grid;
	*/
}

void Board::initBoard(){
	#ifdef DEBUG
	cout << "entered initBoard" << endl;
	#endif
	delete lvl;
	#ifdef DEBUG
	cout << "deleted lvl" << endl;
	#endif
	if (level == 0){
		lvl = new Level0();
		movesRemaining = 20;
		winScore = score + lvl->getWinScore();
	}
	else if (level == 1) {
		lvl = new Level1();
		movesRemaining = 25;
		winScore = score + lvl->getWinScore();
	}
	else if (level == 2) {
		lvl = new Level2();
		movesRemaining = 25;
		winScore = score + lvl->getWinScore();
	}
	lvl->setFileName(fileName);
	grid = lvl->createGrid();
	#ifndef TEXT_ONLY
	for (int r = 0; r < 10; r++){
		for (int c = 0; c < 10; c++){
			grid[r][c]->printToWindow(window);
		}
	}
	#endif
	while(determineMatches()){
		setGridElement(match->row, match->col, lvl->createSquare(match->row, match->col));
		//scramble();
	}

	#ifdef DEBUG
	cout << "created grid" << endl;
	#endif
}

Square*** Board::getGrid(){
	return grid;
}

bool Board::determineMatches(){
	bool matchExists = false;
	for (int row = 0; ((row < 10) && !matchExists); row++){
		for (int col = 0; ((col < 10) && !matchExists); col++){
			if (MatchL::isMatch(row, col, this)){
				matchExists = true;
				match = new MatchL(row, col, this);
			}
			else if (MatchVertical::isMatch(row, col, this)){
				matchExists = true;
				match = new MatchVertical(row, col, this);
			}
			else if(MatchHorizontal::isMatch(row, col, this)){
				matchExists = true;
				match = new MatchHorizontal(row, col, this);
			}
		}
	}
	return matchExists;
}

int Board::executeMatches(){
	#ifdef DEBUG
	cout << "About to executeMatches" << endl;
	#endif
	int cellsDeleted = 0;
	if(match){
		#ifdef DEBUG
		cout << "About to clearCells" << endl;
		cout << "row: " << match->row << ", col: " << match->col << endl;
		#endif
		int matchColour = match->getMatchColour(this);
		cellsDeleted += match->clearCells(this);
		match->insertSpecialSquare(this, matchColour);
		#ifdef DEBUG
		cout << "finished clearCells" << endl;
		#endif	
	}

	#ifdef DEBUG
	cout << "finished executeMatches" << endl;
	#endif
	delete match;
	match = NULL;
	return cellsDeleted;
	
}

void Board::swap (int row, int column, int direction) {
	if (!(row > 10 || row < 1 || column > 10 || column < 1)) {
		Square* temp = grid[row-1][column-1];
		// direction = 0 for north, 1 for south, 2 for west and 3 for east
		if (temp->getAdvSymbol() != "l") {
			if ((direction == 0) && (row > 1) && (grid[row-2][column-1]->getAdvSymbol() != "l")) {
				// setGridElement(int r, int c, Square* sqr)
				setGridElement(row-1, column-1, grid[row-2][column-1]);
				setGridElement(row-2, column-1, temp);
				/*
				grid[row-1][column-1] = grid[row-2][column-1];
				grid[row-2][column-1] = temp;
				*/
				if (!determineMatches()) {
					cout << "invalid move: no matches" << endl;
					setGridElement(row-2, column-1, grid[row-1][column-1]);
					setGridElement(row-1, column-1, temp);
					/*
					grid[row-2][column-1] = grid[row-1][column-1];
					grid[row-1][column-1] = temp;
					*/
				}
				else {
					movesRemaining--;
				}
			}
			else if ((direction == 1) && (row < 10) && (grid[row][column-1]->getAdvSymbol() != "l")) {
				setGridElement(row-1, column-1, grid[row][column-1]); //grid[row-1][column-1] = grid[row][column-1];
				setGridElement(row, column-1, temp); // grid[row][column-1] = temp;
				if (!determineMatches()) {
					cout << "invalid move: no matches" << endl;
					setGridElement(row, column-1, grid[row-1][column-1]);
					setGridElement(row-1, column-1, temp);
					/*
					grid[row][column-1] = grid[row-1][column-1];
					grid[row-1][column-1] = temp;
					*/
				}
				else {
					movesRemaining--;
				}
			}
			else if ((direction == 2) && (column > 1) && (grid[row-1][column-2]->getAdvSymbol() != "l")) {
				setGridElement(row-1, column-1, grid[row-1][column-2]); //grid[row-1][column-1] = grid[row-1][column-2];
				setGridElement(row-1, column-2, temp); //grid[row-1][column-2] = temp;
				if (!determineMatches()) {
					cout << "invalid move: no matches" << endl;
					setGridElement(row-1, column-2, grid[row-1][column-1]); //grid[row-1][column-2] = grid[row-1][column-1];
					setGridElement(row-1, column-1, temp); //grid[row-1][column-1] = temp;
				}
				else {
					movesRemaining--;
				}
			}
			else if ((direction == 3) && (column < 10) && (grid[row-1][column]->getAdvSymbol() != "l")) {
				setGridElement(row-1, column-1, grid[row-1][column]); //grid[row-1][column-1] = grid[row-1][column];
				setGridElement(row-1, column, temp); //grid[row-1][column] = temp;
				if (!determineMatches()) {
					cout << "invalid move: no matches" << endl;
					setGridElement(row-1, column, grid[row-1][column-1]); //grid[row-1][column] = grid[row-1][column-1];
					setGridElement(row-1, column-1, temp); //grid[row-1][column-1] = temp;
				}
				else {
					movesRemaining--;
				}
			}
		}
		else {
			cout << "invalid move" << endl;
		}
	}
}

void Board::getHint() {
	bool hintFound = false;
	for (int i = 0; i<10; i++) {
		for (int j = 0; j<10; j++) {
			Square* temp = grid[i][j];
			if (!hintFound) {
				if (i > 0 && grid[i-1][j]->getAdvSymbol() != "l") { // can swap to the north
					setGridElement(i, j, grid[i-1][j]);
					setGridElement(i-1, j, temp);
					if (determineMatches()) {
						cout << i+1 << " " << j+1 << " " << 0 << endl;
						hintFound = true;
					}
					setGridElement(i-1, j, grid[i][j]);
					setGridElement(i, j, temp);
				} // end of if (i > 0)
				if ((i < 9) && grid[i+1][j]->getAdvSymbol() != "l" && !hintFound) { // can swap to the south
					setGridElement(i, j, grid[i+1][j]);
					setGridElement(i+1, j, temp);
					if (determineMatches()) {
						cout << i+1 << " " << j+1 << " " << 1 << endl;
						hintFound = true;
					}
					setGridElement(i+1, j, grid[i][j]);
					setGridElement(i, j, temp);
				} // end of if (i < 9)
				if ((j > 0) && grid[i][j-1]->getAdvSymbol() != "l" && !hintFound) { // can swap to the west
					setGridElement(i, j, grid[i][j-1]);
					setGridElement(i, j-1, temp);
					if (determineMatches()) {
						cout << i+1 << " " << j+1 << " " << 2 << endl;
						hintFound = true;
					}
					setGridElement(i, j-1, grid[i][j]);
					setGridElement(i, j, temp);
				} // end of if (j > 0)
				if ((j < 9) && grid[i][j+1]->getAdvSymbol() != "l" && !hintFound) { // can swap to the east
					setGridElement(i, j, grid[i][j+1]);
					setGridElement(i, j+1, temp);
					if (determineMatches()) {
						cout << i+1 << " " << j+1 << " " << 3 << endl;
						hintFound = true;
					}
					setGridElement(i, j+1, grid[i][j]);
					setGridElement(i, j, temp);
				} // end of if (j < 9)
			} // end of if (!hintFound)
		}
	}
	if (!hintFound) {
		cout << "no matches possible." << endl;
	}
}

int Board::getPoints(int squares, int chain) {
	if (squares == 3) {
		return squares * pow(2, chain);
	}
	else if (squares == 4) {
		return 2 * squares * pow(2, chain);
	}
	else if (squares == 5) {
		return 3 * squares * pow(2, chain);
	}
	else if (squares > 5) {
		return 4 * squares * pow(2, chain);
	}
	else {
		return 0;
	}
}

void Board::updateBoard() {
	int chainNumber = 0;
	while(determineMatches()){
		int squaresDeleted = executeMatches();
		score += getPoints(squaresDeleted, chainNumber);
		#ifdef DEBUG_FINAL
		cout << "score: " << score << endl;
		#endif
		chainNumber += 1;
		refill();
	}
}

void Board::scramble() {
	#ifdef SCRAM 
	cout << "running scramble" << endl;
	#endif
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j < 8) {
				if (grid[i][j]->getColour() == grid[i][j+1]->getColour() && grid[i][j]->getColour() == grid[i][j+2]->getColour()) {
					Square* temp = grid[i][j+1];
					if (i < 9) {
						if (grid[i][j+1]->getColour() == grid[i+1][j+1]->getColour()) {
							putRandom(i, j+1);
						}
						else {
							setGridElement(i, j+1, grid[i+1][j+1]);
							setGridElement(i+1, j+1, temp);
						}
					}
					else if (i > 0) {
						if (grid[i][j+1]->getColour() == grid[i-1][j+1]->getColour()) {
							putRandom(i, j+1);
						}
						else {
							setGridElement(i, j+1, grid[i-1][j+1]);
							setGridElement(i-1, j+1, temp);
						}
					}
					else {
						putRandom(i, j+1);
					}
				} // end of if(three colours in a row)
			}
			if (i < 8) {
				if (grid[i][j]->getColour() == grid[i+1][j]->getColour() && grid[i][j]->getColour() == grid[i+2][j]->getColour()) {
					Square* temp = grid[i+1][j];
					if (j < 9) {
						if (grid[i+1][j]->getColour() == grid[i+1][j+1]->getColour()) {
							putRandom(i+1, j);
						}
						else {
							setGridElement(i+1, j, grid[i+1][j+1]);
							setGridElement(i+1, j+1, temp);
						}
					}
					else if (j > 0) {
						if (grid[i+1][j]->getColour() == grid[i+1][j-1]->getColour()) {
							putRandom(i+1, j);
						}
						else {
							setGridElement(i+1, j, grid[i+1][j-1]);
							setGridElement(i+1, j-1, temp);
						}
					}
					else {
						putRandom(i, j+1);
					}
				}
			}
		}
	}

	/*for (int i = 0; i < 10; i++) {
		// direction = 0 for north, 1 for south, 2 for west and 3 for east
		x = rand() % 9 + 0;     // x in the range 0 to 9
		y = rand() % 9 + 0;     // y in the range 0 to 9
		dir = rand() % 3 + 0;     // x in the range 0 to 3
		Square* temp = grid[x][y];

		if ((dir == 0) && (x > 0)) {
			setGridElement(x, y, grid[x-1][y]);
			setGridElement(x-1, y, temp);
		}
		else if ((dir == 1) && (x < 9)) {
			setGridElement(x, y, grid[x+1][y]);
			setGridElement(x+1, y, temp);
		}
		else if ((dir == 2) && (y > 0)) {
			setGridElement(x, y, grid[x][y-1]);
			setGridElement(x, y-1, temp);
		}
		else if ((dir == 3) && (y < 9)) {
			setGridElement(x, y, grid[x][y+1]);
			setGridElement(x, y+1, temp);
		}
	}*/
}

void Board::putRandom(int row, int column) {
	Square* temp = grid[row][column];
	int x = rand() % 9 + 0; // random number between 0 and 9
	int y = rand() % 9 + 0; // random number between 0 and 9
	grid[row][column] = grid[x][y];
	grid[x][y] = temp;
}

int Board::getScore() {
	return score;
}

void Board::setScore(int newScore) {
	score = newScore;
}
int Board::getLevel() {
	return level;
}

void Board::setLevel(int newLevel) {
	level = newLevel;
}

int Board::getRemainingMoves() {
	return movesRemaining;
}

void Board::setGrid(Square*** grid) {
	this->grid = grid;
}

void Board::levelup() {
	
	if (level <= 1){
		level++;
		initBoard();	
	} else {
		cout << "No more levels :(" << endl;
	}
}

void Board::leveldown() {
	if (level >=1){
		level--;
		initBoard();
	}
	else {
		cout << "No easier levels :( Try harder." << endl;	
	}
}

int Board::getLockedSquares() {
	return lvl->getLockedSquares();
}

void Board::restart() {
	grid = lvl->createGrid();
	initBoard();
	winScore = score + lvl->getWinScore();
	movesRemaining = 20;
}

int Board::deleteSquare(int r, int c){
	int squaresDeleted = 0;
	
	if ((r < 0) || (r >= 10) || (c < 0) || (c >= 10)){
		return squaresDeleted;
	}

	if (grid[r][c]){
		if (grid[r][c]->getAdvSymbol() == "l") {
			lvl->setLockedSquares(lvl->getLockedSquares() - 1);
		}
		Square* tempSquare = grid[r][c];
		//grid[r][c] = NULL;
		setGridElement(r, c, NULL);
		squaresDeleted += tempSquare->executeAbility(this);
		squaresDeleted += 1;
		delete tempSquare;	
	}

	return squaresDeleted;
}

ostream& operator<< (ostream &out, Board &b) {
	out << "Level: " << b.level << endl;
	out << "Score: " << b.score << endl;
	out << "Winning Score: " << b.winScore << endl;
	out << "Moves remaining: " << b.movesRemaining << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			out << b.grid[i][j]->getRepresentation() << " ";
		}
		out << endl;
	}
	return out;
}

void Board::refill() {
	for (int i = 9; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			if (grid[i][j] == NULL) {
				bool squareFound = false;
				for (int k = i-1; (k >= 0); k--) {
					if (grid[k][j] != NULL && grid[k][j]->getAdvSymbol() != "l") {
						setGridElement(i, j, grid[k][j]);
						grid[i][j]->setCoords(i, j);
						setGridElement(k, j, NULL);
						squareFound = true;
						break;
					}
				}
				if (!squareFound) {
					setGridElement(i, j, lvl->createSquare(i, j));
				} // end of if
			} // end of if
			//grid[i][j]->printToWindow(window);
		} // end of for
	} // end of for
} // end of refill()

void Board::setGridElement(int r, int c, Square* sqr){
	#ifdef DEBUG
	cout << "running setGridElement method" << endl;
	#endif
	if(sqr){
		sqr->setCoords(r, c, window);
		sqr->printToWindow(window);
	}else{
		int dimension = 50;
		if(window){
			window->fillRectangle(c*dimension, r*dimension, dimension, dimension, Square::blackColour);	
		}		
	}
	grid[r][c] = sqr;

}