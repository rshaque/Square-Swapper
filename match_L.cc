#include "match_L.h"
#include "unstablesquare.h"
#include "board.h"

int MatchL::getNumberOfLeftMatches(int row, int col, Board* board){
	Square*** grid = board->getGrid();
	int leftMatches = 0;
	for (int c = (col -2); ((c>=0) && (c<=col)); c++){
		if ((grid[row][c]->getColour()) == (grid[row][col]->getColour())){
			leftMatches += 1;
		}
	}
	return leftMatches;
}

int MatchL::getNumberOfRightMatches(int row, int col, Board* board){
	Square*** grid = board->getGrid();
	int rightMatches = 0;
	for (int c = col; ((c <= (col + 2)) && (c < 10)); c++){
		if ((grid[row][c]->getColour()) == (grid[row][col]->getColour())){
			rightMatches += 1;
		}	
	}
	return rightMatches;
}

int MatchL::getNumberOfAboveMatches(int row, int col, Board* board){
	Square*** grid = board->getGrid();
	int aboveMatches = 0;
	for (int r = (row-2); ((r>=0) && (r<=row)); r++){
		if((grid[r][col]->getColour()) == (grid[row][col]->getColour())){
			aboveMatches += 1;
		}
	}
	return aboveMatches;
}

int MatchL::getNumberOfBelowMatches(int row, int col, Board* board){
	Square*** grid = board->getGrid();
	int belowMatches = 0;
	for (int r = row; ((r <= (row+2)) && (r < 10)); r++){
		if((grid[r][col]->getColour()) == (grid[row][col]->getColour())){
			belowMatches += 1;
		}
	}
	return belowMatches;
}

MatchL::MatchL(int row, int col, Board* board){
	int leftMatches = getNumberOfLeftMatches(row, col, board);
	int rightMatches = getNumberOfRightMatches(row, col, board);
	int aboveMatches = getNumberOfAboveMatches(row, col, board);
	int belowMatches = getNumberOfBelowMatches(row, col, board);

	this->row = row;
	this->col = col;

	if ((leftMatches == 3) && (aboveMatches == 3)){
		endRow = row-2;
		endCol = col-2;
	}
	else if ((leftMatches == 3) && (belowMatches == 3)){
		endRow = row + 2;
		endCol = col - 2;
	}
	else if ((rightMatches == 3) && (aboveMatches == 3)){
		endRow = row - 2;
		endCol = col + 2;
	}
	else if ((rightMatches == 3) && (belowMatches == 3)){
		endRow = row + 2;
		endCol = col + 2;
	}
	length = 5;
}

bool MatchL::isMatch(int row, int col, Board* board){
	int leftMatches = getNumberOfLeftMatches(row, col, board);
	int rightMatches = getNumberOfRightMatches(row, col, board);
	int aboveMatches = getNumberOfAboveMatches(row, col, board);
	int belowMatches = getNumberOfBelowMatches(row, col, board);

	if ((leftMatches == 3) && (aboveMatches == 3)){
		return true;
	}
	if ((leftMatches == 3) && (belowMatches == 3)){
		return true;
	}
	if ((rightMatches == 3) && (aboveMatches == 3)){
		return true;
	}
	if ((rightMatches == 3) && (belowMatches == 3)){
		return true;
	}
	return false;
}

int MatchL::clearCells(Board* board){
	int cellsDeleted = 0;
	int colFactor;
	int rowFactor;

	if (endCol < col){
		colFactor = 1;
	}else {
		colFactor = -1;
	}

	if (endRow < row){
		rowFactor = 1;
	}else{
		rowFactor = -1;
	}

	for (int i = 0; i <= 2; i++){
		cellsDeleted += board->deleteSquare(row, (endCol + (colFactor * i)));
	}
	for (int i =0; i < 2; i++){
		cellsDeleted += board->deleteSquare((endRow + (rowFactor * i)), col);
	}

	return cellsDeleted;
}

bool MatchL::insertSpecialSquare(Board* board, int matchColour){
	Square* special = new UnstableSquare(matchColour, row, col);
	//(board->getGrid())[row][col] = special;
	board->setGridElement(row, col, special);
	return true;
}

int MatchL::getMatchColour(Board* board){
	return (board->getGrid())[row][col]->getColour();
}