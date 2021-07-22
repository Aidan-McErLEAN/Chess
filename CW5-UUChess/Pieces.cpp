/*
* Pieces.cpp
*
* Version information
* Author: Ryan O'Neill
* Date: 19/12/2020
* Description: This is the definition file for class Pieces.
*
* Refer to the header file for more details
*
* Copyright notice -
*/

#include "Pieces.h"
#include "Board.h"

// Below is the rowNumber function, it returns the row number of a given position
int rowNumber(int posNum) {
	if (posNum <= 7 && posNum >= 0) {
		return 1;
	}
	else if (posNum <= 15 && posNum >= 8) {
		return 2;
	}
	else if (posNum <= 23 && posNum >= 16) {
		return 3;
	}
	else if (posNum <= 31 && posNum >= 24) {
		return 4;
	}
	else if (posNum <= 39 && posNum >= 32) {
		return 5;
	}
	else if (posNum <= 47 && posNum >= 40) {
		return 6;
	}
	else if (posNum <= 55 && posNum >= 48) {
		return 7;
	}
	else if (posNum <= 63 && posNum >= 56) {
		return 8;
	}
	else {
		return 0;
	}
}

// Below is the columnNumber function, it returns the column number of a given position
int Pieces::columnNumber(int posNum) {
	int row = rowNumber(posNum);
	if (row == 1) {
		return posNum + 1;
	}
	else {
		if (posNum % 8 == 0) {
			return 1;
		}
		else if ((posNum - 1) % 8 == 0) {
			return 2;
		}
		else if ((posNum - 2) % 8 == 0) {
			return 3;
		}
		else if ((posNum - 3) % 8 == 0) {
			return 4;
		}
		else if ((posNum - 4) % 8 == 0) {
			return 5;
		}
		else if ((posNum - 5) % 8 == 0) {
			return 6;
		}
		else if ((posNum - 6) % 8 == 0) {
			return 7;
		}
		else if ((posNum - 7) % 8 == 0) {
			return 8;
		}
	}
}
// Below is the rowMinimum function, it returns the value of the first space 
// of a given row
int rowMin(int posNum) {
	int rNum = rowNumber(posNum);
	if (rNum >= 1 && rNum <= 8) {
		return (rNum * 8) - 7;
	}
	else {
		return 0;
	}
}
// Below is the rowMaximum function, it returns the value of the last space of
// a given row
int rowMax(int posNum) {
	int rNum = rowNumber(posNum);
	if (rNum >= 1 && rNum <= 8) {
		return rNum * 8;
	}
	else {
		return 0;
	}
}

/* Below is the checkLegitMove function, it checks to see if the move that
 * the piece the user is moving can make the move they are asking of it.
 * e.g. check to see if a pawn can't move sideways. 
 */
bool Pieces::checkLegitMove(int from, int to, std::vector<char> currBoard_) {
	// below is code that sets the piece trying to move to the variable 'piece'
	// it also sets a vector with the values in currBoard_.
	std::vector<char> Board_ = currBoard_;
	char piece = Board_[from];
	Board b; // initiate board as the game engine

	/* the below if statement checks if the piece being moved is a valid
	 * piece and if the space the piece is being moved to is both a real
	 * space on the board and is not equal to the pieces current position 
	 */
	if ((piece >= 'A' && 'Z' >= piece || piece >= 'a' && 'z' >= piece) && from != to && to <= 63 && to >= 0) {


		//bishop basic moves
		if (piece == 'B' || piece == 'b') {
			int total = 0;
			if (from > to) {
				total = from - to;
			}
			else {
				total = to - from;
			}

			if (total % 9 == 0 || total % 7 == 0) {
				return true;
			}
			else {
				return false;
			}
		}

		//rook basic moves
		if (piece == 'R' || piece == 'r') {
			int fromRow = rowNumber(from);
			int toRow = rowNumber(to);
			int fromColumn = columnNumber(from);
			int toColumn = columnNumber(to);
			if (fromRow == toRow || fromColumn == toColumn) {
				return true;
			}
			else {
				return false;
			}
		}

		//pawn basic moves
		if (piece == 'P' || piece == 'p') {
			int fromColumn = columnNumber(from);
			int toColumn = columnNumber(to);
			int fromRow = rowNumber(from);
			int toRow = rowNumber(to);


			if (piece == 'p') {

				if ((fromRow - toRow) == 1) {
					return true;
				}
				else if (fromRow == 7 && toRow == 5) {
					return true;
				}
				else {
					return false;
				}
			}
			else {

				if ((toRow - fromRow) == 1) {
					return true;
				}
				else if (fromRow == 2 && toRow == 4) {
					return true;
				}
				else {
					return false;
				}
			}

		}

		//knight basic moves
		if (piece == 'N' || piece == 'n') {
			int fromColumn = columnNumber(from);
			if (to == (from - 10) && fromColumn != 2 && fromColumn != 1) {
				return true;
			}
			else if (to == (from - 17) && fromColumn != 1) {
				return true;
			}
			else if (to == (from - 15) && fromColumn != 8) {
				return true;
			}
			else if (to == (from - 6) && fromColumn != 8 && fromColumn != 7) {
				return true;
			}
			else if (to == (from + 6) && fromColumn != 1 && fromColumn != 2) {
				return true;
			}
			else if (to == (from + 15) && fromColumn != 1) {
				return true;
			}
			else if (to == (from + 17) && fromColumn != 8) {
				return true;
			}
			else if (to == (from + 10) && fromColumn != 7 && fromColumn != 8) {
				return true;
			}
			else {
				return false;
			}
		}

		//queen basic moves
		if (piece == 'Q' || piece == 'q') {
			int fromRow = rowNumber(from);
			int toRow = rowNumber(to);
			int fromColumn = columnNumber(from);
			int toColumn = columnNumber(to);
			int total = 0;
			if (from > to) {
				total = from - to;
			}
			else {
				total = to - from;
			}

			if (fromRow == toRow || fromColumn == toColumn) {
				return true;
			}
			else if (total % 9 == 0 || total % 7 == 0) {
				return true;
			}
			else {
				return false;
			}
		}

		//king basic moves
		if (piece == 'K' || piece == 'k') {
			int fromColumn = columnNumber(from);
			int toColumn = columnNumber(to);
			if ((fromColumn == 1 && toColumn == 8) || (fromColumn == 8 && toColumn == 1)) {
				return false;
			}
			else {
				if (to == (from - 1)) {
					return true;
				}
				else if (to == (from - 9)) {
					return true;
				}
				else if (to == (from - 8)) {
					return true;
				}
				else if (to == (from - 7)) {
					return true;
				}
				else if (to == (from + 1)) {
					return true;
				}
				else if (to == (from + 9)) {
					return true;
				}
				else if (to == (from + 8)) {
					return true;
				}
				else if (to == (from + 7)) {
					return true;
				}
				else if (to == (from + 2) && from == 4 && piece == 'K') {
					return true;
				}
				else if (to == (from - 2) && from == 4 && piece == 'K') {
					return true;
				}
				else if (to == (from + 2) && from == 60 && piece == 'k') {
					return true;
				}
				else if (to == (from - 2) && from == 60 && piece == 'k') {
					return true;
				}
				else {
					return false;
				}
			}

		}

	}
	else {
		return false;
	}
}
/* below is the getMoveCoordinates function it gets the coordinates of
 * every move a piece can make
 */
int* Pieces::getMoveCoordinates(int sPoint, std::vector<char> currBoard_) {
	int arr[64];
	for (int i = 0; i < 64; i++) {
		if (checkLegitMove(sPoint, i, currBoard_) == true) {
			arr[i] = i;
		}
	}
	return arr;


}