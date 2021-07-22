/*
* Pieces.h
*
* Version information
* Author: Ryan O'Neill
* Date: 19/12/2020
* Description: This is the interface file for the chess pieces class.
*
* You are allowed to add any functions relevant to behaviour of the chess pieces
* This is NOT mandatory, and will depends entirey on your implementation
*
* You can ADD the necessary (pass-by-value) parameters for the function
*
* Copyright notice -
*/

#pragma once

#include <string>
#include <iostream>
#include <vector>


class Pieces
{

public:
    // Default constructor for Pieces - you can use this for initialisation
    Pieces() {};

    /* below is calling the checkLegitMove function. it is passing through two integers
     *   and a vector. the vector is what stores the pieces, and the two integers
     *  are the values of the spaces the selected piece is moving to and from.
     *  checkLegitimateMove then checks if a piece can make that move and returns
     *  true if it can or false if it can't.
     *
     * e.g. a pawn can move one space
     * forwards so this move would return true, however a pawn cannot move
     * sideways so this move would return false. - Ryan
     */
    bool checkLegitMove(int, int, std::vector<char>);

    /* below is the getMoveCoordinates function, it returns all possible coordinates
     * a piece can move to from its current position as an array. - Ryan
     */
    int* getMoveCoordinates(int, std::vector<char>);

    int columnNumber(int);

private:
    enum class Pname_ { Pawn, Rook, Knight, Bishop, Queen, King };
};