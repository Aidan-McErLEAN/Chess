/*
* UI.h
*
* Version information
* Author: Effirul Ramlan
* Date: 20 August 2020
* Description: This is the interface file for the User Interface (UI) class.
*
* Copyright notice -
*/

/****************************************
* DO NOT CHANGE THE CONTENT OF THIS FILE
*****************************************/

#pragma once
#include <iostream>
#include <vector>
#include <string>

#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF
#define EMPTY_SQUARE 0x20

class UI
{

public:
    void printBoard(std::vector<char>); // Print the chess board given the current board vector
    void getMove(); // interface to get input from user
    void removeMove(); // remove illegal move from the list
    int getListMovesIdx() const; // return total no of index - utility function
    std::string getCurrentMove() const; // return the current move
    std::vector<std::string> returnListMoves() const; // return list of all moves

private:
    std::string currMove_; // current move from user
    std::vector<std::string> listMoves_; // vector to store all moves

};


