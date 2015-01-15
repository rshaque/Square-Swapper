#include "lateralsquare.h"
#include "board.h"
#include <string.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
	bool seedSet = false;
	string fileName = "no file";
	int lvlNum = 0;
	bool textOnly = false;
	string colourScheme = "default";
	for (int i = 1; i < argc; i++){
		if (strcmp(argv[i], "-seed") == 0) {
			int x = atoi(argv[i+1]);
			srand(x);
			seedSet = true;
		}
		else if (strcmp(argv[i], "-scriptfile") == 0) {
			fileName = argv[i+1];
		}
		else if (strcmp(argv[i], "-startlevel") == 0) {
			lvlNum = atoi(argv[i+1]);
		}
		else if (strcmp(argv[i], "-text") == 0){
			textOnly = true;
		}
		else if (strcmp(argv[i], "-colourscheme")==0){
			colourScheme = argv[i+1];
		}
	}

	if (!seedSet) {
		srand(time(NULL));
	}

	Board* b = new Board(fileName, lvlNum, textOnly, colourScheme);
	cout << " ||====================================================================|| " << endl;
	cout << " ||                                                                    || " << endl;
	cout << " ||             SSSSS  QQQQQ  U   U    A    RRRR   EEEEE               || " << endl;
	cout << " ||             S      Q   Q  U   U   A A   R   R  E                   || " << endl;
	cout << " ||             SSSSS  Q   Q  U   U  AAAAA  RRRR   EEEE                || " << endl;
	cout << " ||                 S  Q Q Q  U   U A     A R   R  E                   || " << endl;
	cout << " ||             SSSSS  QQQQQQ  UUU  A     A R    R EEEEE               || " << endl;
	cout << " ||                                                                    || " << endl;
	cout << " ||         SSSSS W         W    A    PPPPP PPPPP EEEEE RRRR           || " << endl;
	cout << " ||         S     W    W    W   A A   P   P P   P E     R   R          || " << endl;
	cout << " ||         SSSSS  W  W W  W   AAAAA  PPPPP PPPPP EEEE  RRRR           || " << endl;
	cout << " ||             S  W  W W  W  A     A P     P     E     R   R          || " << endl;
	cout << " ||         SSSSS   WW   WW   A     A P     P     EEEEE R    R         || " << endl;
	cout << " ||                                                                    || " << endl;
	cout << " ||                      555555  000   000   000                       || " << endl;
	cout << " ||                      5      0   0 0   0 0   0                      || " << endl;
	cout << " ||                      55555  0   0 0   0 0   0                      || " << endl;
	cout << " ||                           5 0   0 0   0 0   0                      || " << endl;
	cout << " ||                      55555   000   000   000                       || " << endl;
	cout << " ||                                                                    || " << endl;
	cout << " ||====================================================================|| " << endl << endl;
	cout << "Welcome to SquareSwapper5000! You can play the game using the following commands:" << endl << endl;
	cout << "-> swap x y z:" << endl << "     swaps the square at the (x,y) co-ordinate with the square in the z direction (0 for north, 1 for south, 2 for west and 3 for east)" << endl;
	cout << "-> hint:" << endl << "     the game returns a valid move (x,y, z as above) that would lead to a match." << endl;
	cout << "-> scramble:" << endl << "     Available only if no moves are possible, this command reshuffles the squares on the board (no new cells are created)" << endl;
	cout << "-> levelup:" << endl << "     Increases the difficulty level of the game by one. You may clear the board and create a new one suitable for that level. If there is no higher level, this command has no eﬀect." << endl;
	cout << "->leveldown:" << endl << "     The same as above, but this time decreasing the difficulty level of the game by one." << endl;
	cout << "->restart:" << endl << "     Clears the board and starts a new game at the same level" << endl << endl;
	string input;
	string swapFunc = "swap";
	string hintFunc = "hint";
	string scrambleFunc = "scramble";
	string levelupFunc = "levelup";
	string leveldownFunc = "leveldown";
	string colourFunc = "colourscheme";
	string restartFunc = "restart";
	string renameFunc = "rename";
	string quitFunc = "quit";

	while (b->getRemainingMoves() > 0) {
		if (b->score >= b->winScore && b->getLockedSquares() == 0) {
			cout << "Congratulations! You beat the level! :)" << endl;
			b->levelup();
		}
		cout << *b;
		cin >> input;
		if (input == swapFunc) {
			int x, y, d;
			cin >> x >> y >> d;
			b->swap(x,y,d);
			b->updateBoard();
		}
		else if (input == hintFunc) {
			b->getHint();
		}
		else if (input == scrambleFunc) {
			// check if there are moves remaining
			b->scramble();
		}
		else if (input == levelupFunc) {
			b->levelup();
		}
		else if (input == leveldownFunc) {
			b->leveldown();
		}
		else if (input == restartFunc) {
			b->restart();
		}
		else if (input == renameFunc) {
			cin >> input;
			if (input == swapFunc) {
				cin >> input;
				swapFunc = input;
			}
			else if (input == hintFunc) {
				cin >> input;
				hintFunc = input;
			}
			else if (input == scrambleFunc) {
				cin >> input;
				scrambleFunc = input;
			}
			else if (input == levelupFunc) {
				cin >> input;
				levelupFunc = input;
			}
			else if (input == leveldownFunc) {
				cin >> input;
				leveldownFunc = input;
			}
			else if (input == colourFunc) {
				cin >> input;
				colourFunc = input;
			}
			else if (input == restartFunc) {
				cin >> input;
				restartFunc = input;
			}
			else if (input == renameFunc) {
				cin >> input;
				renameFunc = input;
			}
			else if (input == quitFunc) {
				cin >> input;
				quitFunc = input;
			}
		}
		else if (input == quitFunc) {
			cout << "Thanks for playing!" << endl;
			break;
		}
		
	}
}