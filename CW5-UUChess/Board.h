/*
* Board.h
*
* Version information
* Author: Kamil Lukasik & Aidan McErlean
* Date: 19/12/2020
* Description: This is the interface file for the chess board class.
*
* Copyright notice -
*/

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Board
{

public:
    // Default constructor - assign the current board to the start board 
    Board() {
        currBoard_ = initBoard_;
    };

    /*global variables which store what pieces are getting moved and taken
    * stores both the cell value, and index as well as a counter to keep
    * track of moves - Kamil
    */

    char piece;
    char pieceTo;
    int to;
    int from;
    int counter_;

    /**************************************************************
    * Utility function for the keep-track and update for the board
    ***************************************************************/

    // Return the initial setup for the board
    std::vector<char> getInitBoard() const;

    // Return the current state of the board
    std::vector<char> getCurrentBoard() const;

    // Update the currBoard_ using the new position (e.g., A4, C5, etc) - Aidan McErlean.
    void updateBoard(std::string newPosition);

    /* Functions to validate the new move, depending on the checkLegitMove function and
    * traverseCell. This method checks if the destination coordinate is valid for the
    * type of move entered. It allows for taking enemy pieces, disables you from taking
    * your own piece regular advancement moves and castling. - Kamil.
    */
    bool validateMove();

    /*Method that follows the journey of each piece as it tries to complete each of its moves.
    * checks for all pieces, except the knight (which can jump over pieces) and makes sure that
    * no pieces are in the way before allowing it to move. improper moves SHOULDNT be allowed if any
    * piece is found in any cell in the path that isnt the last one. - Kamil.
    */
    bool traverseCell(char, int, int);

    /* turn uses the counter, as well as blackTurn and White turn to determine whos turn it is,
    * uses the rule that white goes first, and can only move the white (uppercase) pieces and vice versa
    * Makes it so that you cant move a piece that is not yours - Kamil.
    */
    bool turn(std::string);
    bool blackTurn();
    bool whiteTurn();

    

    /*This method will pass through the substrings and the mapBoard_ to the getIndex method. - Aidan McErlean.
    */
    void getValue(std::string);

    /*The methods below, will obtain all the black pieces possbile movements & the white pieces possbile movements,
    * then the movements is stored in a int vector and the vector is returned. - Aidan McErlean.
    */
    std::vector<int> getAllWhiteMoves();
    std::vector<int> getAllBlackMoves();

    /* Functions to check for the current status of the board, whether there is
    *  a CHECK or CHECK-MATE situations. - Aidan McErlean.
    */
    bool checkBoardStatus();


private:
    // The initial setup of the board using char
    std::vector<char> initBoard_ = { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', \
                                'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', \
                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, \
                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, \
                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, \
                                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, \
                                'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', \
                                'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' };

    /* The corresponding board position according to the grid
    *  For the vector we see the coordinates as integer in the form of:
    *       00 - 07, 08 - 15, 16 - 23, 24 - 31, 32 - 39, 40 - 47, 48 - 55, 56 - 63
    *       A1 - H1, A2 - H2, A3 - H3, A4 - H4, A5 - H5, A6 - H6, A7 - H7, A8 - H8
    */
    std::vector<std::string> mapBoard_ = { "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
                                           "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
                                           "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
                                           "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
                                           "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
                                           "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
                                           "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
                                           "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8" };

    std::vector<char> currBoard_; // vector representing the current board position
    std::vector<char> listCaptured_;  // vector representing the captured pieces

    //why is this here? literally breaks my code. can i get rid of it, idk?....too bad!
    //Pieces chessP; // Pieces object

};
