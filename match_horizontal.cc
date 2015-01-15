#include "match_horizontal.h"
#include "lateralsquare.h"
#include "psychedelicsquare.h"
#include "board.h"

MatchHorizontal::MatchHorizontal(int row, int col, Board* board){
	int matchLength = 0;
	Square*** grid = board->getGrid();
	for (int c = col; c < 10; c++){
		if ((grid[row][col]->getColour()) == (grid[row][c]->getColour())){
			matchLength += 1;
		}else{
			break;
		}
	}
	this->row = row;
	this->col = col;
	this->length = matchLength;
}

bool MatchHorizontal::isMatch(int row, int col, Board* board){
	Square*** grid = board->getGrid();
	int matchLength = 0;
	for (int c = col; c < 10; c++){
		if ((grid[row][col]->getColour()) == (grid[row][c]->getColour())){
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

int MatchHorizontal::clearCells(Board* board){
	int cellsDeleted = 0;
	for (int c = col; c < (col + length); c++){
		cellsDeleted += board->deleteSquare(row, c);
	}
	return cellsDeleted;
}

bool MatchHorizontal::insertSpecialSquare(Board* board, int matchColour){
	if (length <= 3){
		return false;
	}else{
		Square* special;
		int special_col = (col+length-1+col)/2;
		if (length == 4){		
			special = new LateralSquare(matchColour, row, special_col);			
		} else if (length == 5){
			special = new PsychedelicSquare(matchColour, row, special_col);
		} else{
			special = NULL;
		}
		//(board->getGrid())[row][special_col] = special;
		board->setGridElement(row, special_col, special);
		return true;
	}
}

int MatchHorizontal::getMatchColour(Board* board){
	return (board->getGrid())[row][col]->getColour();
}