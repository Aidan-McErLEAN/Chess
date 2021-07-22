/*
* UI.cpp
*
* Version information
* Author: Effirul Ramlan
* Date: 20 August 2020
* Description: This is the definition file for the User Interface (UI) class.
*
* Copyright notice -
*/

/****************************************
* DO NOT CHANGE THE CONTENT OF THIS FILE
*****************************************/

#include "UI.h"

// print initial board - with initboard_ as initial board setup
void UI::printBoard(std::vector<char> board) {
	int c_width = 6;
	int c_length = c_width / 2;

	std::cout << "   A     B     C     D     E     F     G     H\n\n";
	int idx = 0; // vector index

	// loop for vertical print out (8 cells)
	for (int q = 0; q < 8; q++) {
		// determine cell colors
		int col_c1, col_c2;

		if (q % 2 == 0) {
			col_c1 = WHITE_SQUARE;
			col_c2 = BLACK_SQUARE;
		}
		else {
			col_c1 = BLACK_SQUARE;
			col_c2 = WHITE_SQUARE;
		}

		// print horizontol cells (8 cells)
		for (int p = 0; p < c_length; p++) {
			for (int i = 0; i < 8; i++) {
				if (i % 2 == 0) {
					for (int j = 0; j < c_width; j++) {
						if (p % 2 != 0 && j == 3) {
							std::cout << char(board.at(idx) != 0x20 ? board.at(idx) : col_c1);
							idx++;
						}
						else {
							std::cout << char(col_c1);
						}
					}
				}
				else {
					for (int k = 0; k < c_width; k++) {
						if (p % 2 != 0 && k == 3) {
							std::cout << char(board.at(idx) != 0x20 ? board.at(idx) : col_c2);
							idx++;
						}
						else {
							std::cout << char(col_c2);
						}
					}
				}
			}
			if (p % 2 != 0) {
				std::cout << "  " << q + 1;
			}
			std::cout << std::endl;
		}
	}

	if (!listMoves_.empty()) {
		std::cout << "LAST MOVE: " << listMoves_.back() << std::endl;
	}
}

std::string UI::getCurrentMove() const {
	return currMove_;
}

std::vector < std::string> UI::returnListMoves() const {
	return listMoves_;
}

// Utility function to check the syntax and length of user input
bool checkLength(std::string str) {
	if (str.length() != 5) {
		return false;
	}
	else {
		// We need to check the input
		if (str[0] < 65 || str[0] > 72) {
			return false;
		}
		else if (str[1] < 49 || str[1] > 56) {
			return false;
		}
		else if (str[2] != '-') {
			return false;
		}
		else if (str[3] < 65 || str[3] > 72) {
			return false;
		}
		else if (str[4] < 49 || str[4] > 56) {
			return false;
		}
	}
	return true;
}

std::string strToUpper(std::string str) {
	for (char& ch : str) {
		ch = std::toupper(ch);
	}
	return str;
}

void UI::getMove() {
	std::cout << "\nYour move: \n";
	getline(std::cin, currMove_);
	currMove_ = strToUpper(currMove_);

	// Perform checks for the new input
	// 1 - Check string is the correct syntax
	// 2 - Make sure the selected position is NOT empty
	while (!checkLength(currMove_)) {
		std::cout << "Invalid move - Err1: syntax should be XX-XX\n";
		std::cout << "\nYour move: \n";
		getline(std::cin, currMove_);
		currMove_ = strToUpper(currMove_);
	}
	listMoves_.push_back(currMove_);
}

void UI::removeMove() {
	listMoves_.pop_back();
}

int UI::getListMovesIdx() const {
	return (int)listMoves_.size();
}