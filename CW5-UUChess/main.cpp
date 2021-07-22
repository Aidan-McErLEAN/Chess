/*
* main.cpp
*
* Version information
* Author: Kamil Lukasik, Aidan McErlean & Ryan O'Neill
* Date: 19/12/2020
* Description : This file is the driver for the application.
*
* Copyright notice -
*/

#include "Pieces.h"
#include "Board.h"
#include "UI.h"
#include <iostream>

using namespace std;

int main()
{
	Board b; // initiate board as the game engine
	UI UIboard; // initiate UI object for interfacing

	b.counter_ = 1; // initiate counter
	UIboard.printBoard(b.getInitBoard()); //print the board
	b.checkBoardStatus(); // check if a win condition is met

	
	// USED FOR TESTING //
	/* 
	string moves[] = { "E2-E4","C7-C5", "C2-C3","D7-D5", "E4-D5","D8-D5", "D2-D4","G8-F6", "G1-F3","C8-G4",
	"F1-E2","E7-E6", "H2-H3","G4-H5", "E1-G1","B8-C6", "C1-E3","C5-D4", "C3-D4","F8-B4", "A2-A3","B4-A5",
	"B1-C3","D5-D6", "C3-B5","D6-E7", "F3-E5","H5-E2", "D1-E2","E8-G8", "A1-C1","A8-C8", "E3-G5","A5-B6", 
	"G5-F6","G7-F6", "E5-C4","F8-D8", "C4-B6","A7-B6", "F1-D1","F6-F5", "E2-E3","E7-F6", "D4-D5","D8-D5",
	"D1-D5","E6-D5", "B2-B3","G8-H8", "E3-B6","C8-G8", "B6-C5","D5-D4", "B5-D6","F5-F4", "D6-B7","C6-E5", 
	"C5-D5","F4-F3", "G2-G3","E5-D3", "C1-C7","G8-E8", "B7-D6","E8-E1", "G1-H2", "D3-F2", "D6-F7","H8-G7",
	"F7-G5","G7-H6", "C7-H7" };
	
	for (int i = 0; i < size(moves); i++) {

		string currMove_ = moves[i];

		if (b.turn(currMove_)) {

			if (b.validateMove() == false) {
				UIboard.printBoard(b.getCurrentBoard());
				cout << "Invalid move, try again! Please try again!" << endl;
				std::cout << currMove_ << std::endl;
			}

			else {
				b.updateBoard(currMove_);
				b.counter_++;
				UIboard.printBoard(b.getCurrentBoard());
				std::cout << currMove_ << std::endl;
				b.checkBoardStatus();
			}

		}
	}
	*/
	
	while (b.checkBoardStatus() == false && b.counter_ <= 100) { // while wincondition is not met, do this

		UIboard.getMove();       // get a user input move 
		string currMove_ = UIboard.getCurrentMove();

		if (b.turn(currMove_)) { // check whose turn it is
			if (b.validateMove() == false) {  // validate the input move as long as a correct piece is moved
				UIboard.printBoard(b.getCurrentBoard());  // reprint the board and let user try again
				cout << "invalid move try again" << endl;
			}
			else {
				b.updateBoard(currMove_);    // if move is valid update the board
				b.counter_++;               // increase counter to advance turn
				UIboard.printBoard(b.getCurrentBoard()); // print the updated board and loop again
			}
		}
	}
	//I had fun making this - Kamil
}

