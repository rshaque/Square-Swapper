#include "square.h"
#include <iostream>
#include "window.h"

using namespace std;

enum {White=0, Black, Red, Green, Blue};

void Square::setCoords(const int &row, const int &column){
	this->row = row;
	this->column = column;
	//window->fillRectangle(row*dimension, column*dimension, dimension, dimension, colour);
}

void Square::setColour(int colour) {
	this->colour = colour;
}

void Square::setAdvSymbol(string sym) {
	this->advancedSymbol = sym;
}

int Square::getColour(){
	return colour;
}

int Square::getRow(){
	return row;
}

int Square::getColumn(){
	return column;
}

string Square::getSqSymbol() {
	return squareSymbol;
}

string Square::getAdvSymbol() {
	return advancedSymbol;
}

void Square::setWindow (Xwindow* window){
	this->window = window;
}

void Square::printToWindow(Xwindow* window){
	if (window){
		int dimension = 50;
		window->fillRectangle(column*dimension, row*dimension, dimension, dimension, colour);
		#ifdef COLOUR_DEBUG
		cout << "setting row: " << row <<", column: " << column << ", as colour: " << colour << endl;
		#endif
		printToWindowSpecial(window);
		if (getAdvSymbol() == "l"){
			printLockedToWindow(window);
		}	
	}
}

void Square::printLockedToWindow(Xwindow* window){
	int dimension = 50;
	int x = column * dimension;
	int y = row * dimension;
	int width = 4;
	int offset = 2;
	int length = dimension - (2 * offset);	
	window->fillRectangle(x+offset, y+offset, width, length, blackColour);
	window->fillRectangle(x+offset, y+offset, length, width, blackColour);
	window->fillRectangle(x+offset, y+dimension-width-offset, length, width, blackColour);
	window->fillRectangle(x+dimension-width-offset, y+offset, width, length, blackColour);
}

void Square::setCoords(const int &row, const int &column, Xwindow* window){
	//int dimension = 50;
	//window->fillRectangle(this->column*dimension, this->row*dimension, dimension, dimension, colour);
	this->row = row;
	this->column = column;
	printToWindow(window);	
}

int Square::blackColour = 7;