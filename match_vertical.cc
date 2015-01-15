#include "match_vertical.h"
#include "uprightsquare.h"
#include "psychedelicsquare.h"
#include "board.h"

MatchVertical::MatchVertical(int row, int col, Board* board){
	int matchLength = 0;
	Square*** grid = board->getGrid();
	for (int r = row; r < 10; r++){
		if((grid[row][col]->getColour()) == (grid[r][col]->getColour())){
			matchLength += 1;
		}else{
			break;
		}
	}
	this->row = row;
	this->col = col;
	this->length = matchLength;
}

bool MatchVertical::isMatch(int row, int col, Board* board){
	Square*** grid = board->getGrid();
	int matchLength = 0;
	for (int r = row; r < 10; r++){
		if((grid[row][col]->getColour()) == (grid[r][col]->getColour())){
			matchLength += 1;
		}else{
			break;
		}
	}
	if (matchLength >= 3){
		return true;
	}
	return false;
}

bool MatchVertical::insertSpecialSquare(Board* board, int matchColour){
	if (length <= 3){
		return false;
	}else{
		Square* square;
		int specialRow = (row + length - 1 + row) / 2;
		if(length == 4){
			square = new UprightSquare(matchColour, specialRow, col);
		}else if (length == 5){
			square = new PsychedelicSquare(matchColour, specialRow, col);
		}else{
			square = NULL;
		}
		//(board->getGrid())[specialRow][col] = square;
		board->setGridElement(specialRow, col, square);
		return true;
	}
}

int MatchVertical::clearCells(Board* board){
	int cellsDeleted = 0;
	for (int r = row; r < (row + length); r++){
		cellsDeleted += board->deleteSquare(r, col);
	}
	return cellsDeleted;
}

int MatchVertical::getMatchColour(Board* board){
	return (board->getGrid())[row][col]->getColour();
}