#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <string>

class Board;
class Xwindow;

class Square {
	
	protected:
	int colour;
	int row;
	int column;
	std::string advancedSymbol;
	std::string squareSymbol;
	Xwindow* window;

	
public:
	static int blackColour;
	// virtual executeAbility(Board* board) = 0;
	virtual std::string getRepresentation() = 0;
	virtual int executeAbility(Board* board) = 0;
	void setCoords(const int &row, const int &column);
	void setCoords(const int &row, const int &column, Xwindow* window);
	void setColour(int colour);
	void setAdvSymbol(std::string sym);
	void setWindow (Xwindow* window);
	void printToWindow(Xwindow* window);
	void printLockedToWindow(Xwindow* window);
	virtual void printToWindowSpecial(Xwindow* window) = 0;
	int getColour();
	int getRow();
	int getColumn();
	std::string getSqSymbol();
	std::string getAdvSymbol();
	//Square();
};

#endif