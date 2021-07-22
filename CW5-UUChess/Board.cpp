/*
* Board.cpp
*
* Version information
* Author: Kamil Lukasik & Aidan McErlean
* Date: 19/12/2020
* Description: This is the definition file for class Board.
*
* Refer to the header file for more details
*
* Copyright notice -
*/
#include "UI.h"
#include "Board.h"
#include "Pieces.h"

std::vector<char> Board::getInitBoard() const {
    return initBoard_;
}


std::vector<char> Board::getCurrentBoard() const {
    return currBoard_;
}

/*This method will find the index of a string vector using the string and return the index in an int variable.
* This method is passed the substring e.g (A2), created from updateBoard method & the mapBoard_ from Board.h.
* - Aidan McErlean.
*/
int getIndex(std::vector<std::string> v, std::string K) {
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end()) {
        int index = it - v.begin();
        return index;
    }
}


void Board::getValue(std::string newPosition) {
    //substrings the string for example, "A2-A4" to "A2" & "A4"
    std::string piece_temp = newPosition.substr(0, 2);
    std::string to_temp = newPosition.substr(3, 2);
    //passes the substrings & mapBoard to getIndex method and stores return in from and to int
    from = getIndex(mapBoard_, piece_temp);
    to = getIndex(mapBoard_, to_temp);
    //piece and pieceto char is to store the users from piece and the users to piece
    piece = Board::currBoard_[from];
    pieceTo = Board::currBoard_[to];
}


bool Board::blackTurn() {
    //black always goes second, and can only move their own lowercase pieces
    if ((currBoard_[from] == 'P' || currBoard_[from] == 'R' ||
        currBoard_[from] == 'B' || currBoard_[from] == 'Q' || currBoard_[from] == 'N' || currBoard_[from] == 'K')) {
        return false;
    }
    else {
        return true;
    }
}


bool Board::whiteTurn() {
    // white always goes first and can only move their own lowercase letters
    if ((currBoard_[from] == 'p' || currBoard_[from] == 'r' ||
        currBoard_[from] == 'b' || currBoard_[from] == 'q' || currBoard_[from] == 'n' || currBoard_[from] == 'k')) {
        return false;
    }
    else {
        return true;
    }
}


bool Board::turn(std::string newPosition) {
    //this is where the turn magic happens, depending on the counter
    getValue(newPosition);

    if (counter_ % 2 == 0 && blackTurn() == false) {
        std::cout << "Not your piece try again" << std::endl;
        return false;
    }
    else if (counter_ % 2 != 0 && whiteTurn() == false) {
        std::cout << "Not your piece try again" << std::endl;
        return false;
    }
    else if (counter_ % 2 == 0 && blackTurn() == true) {

        return true;
    }
    else if (counter_ % 2 != 0 && whiteTurn() == true) {

        return true;
    }
}


void Board::updateBoard(std::string newPosition) {
    //passes user input string to getValue method.
    getValue(newPosition);
    //updates the board
    Board::currBoard_[to] = Board::currBoard_[from];
    Board::currBoard_[from] = 0x20;
}


bool Board::traverseCell(char piece, int to, int from) {

    int spaces = to - from;
    bool returnType = false;
    Pieces p;
    //pawn movement and taking 
    if (piece == 'P') {
        if (to == from + 8 || to == from + 16) {
            for (int i = from + 8; i <= to; i += 8) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if (to == from + 9) {
            for (int i = from + 9; i <= to; i += 9) {
                if (pieceTo == 'p' || pieceTo == 'r' || pieceTo == 'n' || pieceTo == 'b' || pieceTo == 'q') {
                    return true;
                }
            }
            returnType = false;
        }
        else if (to == from + 7) {
            for (int i = from + 7; i <= to; i += 7) {
                if (pieceTo == 'p' || pieceTo == 'r' || pieceTo == 'n' || pieceTo == 'b' || pieceTo == 'q') {
                    return true;
                }
            }
            returnType = false;
        }
    }
    else if (piece == 'p') {
        if (to == from - 8 || to == from - 16) {
            for (int i = from - 8; i >= to; i -= 8) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if (to == from - 9) {
            for (int i = from - 9; i >= to; i -= 9) {
                if (pieceTo == 'P' || pieceTo == 'R' || pieceTo == 'N' || pieceTo == 'B' || pieceTo == 'Q') {
                    return true;
                }
            }
            returnType = false;
        }
        else if (to == from - 7) {
            for (int i = from - 7; i >= to; i -= 7) {
                if (pieceTo == 'P' || pieceTo == 'R' || pieceTo == 'N' || pieceTo == 'B' || pieceTo == 'Q') {
                    return true;
                }
            }
            returnType = false;
        }
    }
    //bishop cant jump over pieces, heres how
    else if (piece == 'B' || piece == 'b') {
        if ((spaces) > 0 && (spaces) % 9 == 0) {

            for (int i = from + 9; i < to; i += 9) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if ((spaces) < 0 && (spaces) % 9 == 0) {
            for (int i = from - 9; i > to; i -= 9) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if ((spaces) > 0 && (spaces) % 7 == 0) {
            for (int i = from + 7; i < to; i += 7) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if ((spaces) < 0 && (spaces) % 7 == 0) {
            for (int i = from - 7; i > to; i -= 7) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
    }
    //nothing stands in the way of the rook, nvm i lied heres why
    else if (piece == 'R' || piece == 'r') {
        if (spaces > 0 && spaces % 8 == 0) {
            for (int i = from + 8; i < to; i += 8) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if (spaces < 0 && spaces % 8 == 0) {
            for (int i = from - 8; i > to; i -= 8) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if (7 >= spaces && spaces >= 1 && (0 <= from <= 7 && 0 <= to <= 7
            || 8 <= from <= 15 && 8 <= to <= 15 || 16 <= from <= 23 && 16 <= to <= 23
            || 24 <= from <= 31 && 24 <= to <= 31 || 32 <= from <= 39 && 32 <= to <= 39
            || 40 <= from <= 47 && 40 <= to <= 47 || 48 <= from <= 55 && 48 <= to <= 55
            || 56 <= from <= 63 && 56 <= to <= 63)) {
            for (int i = from + 1; i < to; i++) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if (-7 <= spaces && spaces <= -1 && (0 <= from <= 7 && 0 <= to <= 7
            || 8 <= from <= 15 && 8 <= to <= 15 || 16 <= from <= 23 && 16 <= to <= 23
            || 24 <= from <= 31 && 24 <= to <= 31 || 32 <= from <= 39 && 32 <= to <= 39
            || 40 <= from <= 47 && 40 <= to <= 47 || 48 <= from <= 55 && 48 <= to <= 55
            || 56 <= from <= 63 && 56 <= to <= 63)) {
            for (int i = from - 1; i > to; i--) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
        }
        returnType = true;
    }
    //king only moves one space, so i handled castling here instead
    else if (piece == 'K') {
        if (spaces == 2) {
            for (int i = from + 2; i <= to; i += 2) {
                if (currBoard_[to] != 0x20) {
                    return false;
                }
            }
        }
        else {
            for (int i = from - 2; i >= to; i -= 2) {
                if (currBoard_[to] != 0x20) {
                    return false;
                }
            }
        }
        returnType = true;
    }
    else if (piece == 'k') {
        if (spaces == 2) {
            for (int i = from + 2; i <= to; i += 2) {
                if (currBoard_[to] != 0x20) {
                    return false;
                }
            }
        }
        else {
            for (int i = from - 2; i >= to; i -= 2) {
                if (currBoard_[to] != 0x20) {
                    return false;
                }
            }
        }
        returnType = true;
    }
    //queen is relly just a mashup of a rook and bishop, still cant jump over pieces though 
    else if (piece == 'Q' || piece == 'q') {
        if (spaces > 0 && spaces % 8 == 0) {
            for (int i = from + 8; i < to; i += 8) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if (spaces < 0 && spaces % 8 == 0) {
            for (int i = from - 8; i > to; i -= 8) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if (7 >= spaces && spaces >= 1 && (0 <= from <= 7 && 0 <= to <= 7 || 8 <= from <= 15 && 8 <= to <= 15
            || 16 <= from <= 23 && 16 <= to <= 23 || 24 <= from <= 31 && 24 <= to <= 31 || 32 <= from <= 39 && 32 <= to <= 39
            || 40 <= from <= 47 && 40 <= to <= 47 || 48 <= from <= 55 && 48 <= to <= 55
            || 56 <= from <= 63 && 56 <= to <= 63)) {
            for (int i = from + 1; i < to; i++) {
                if (currBoard_[i] != 0x20) {
                    returnType = false;
                }
            }
            returnType = true;
        }
        else if (-7 <= spaces && spaces <= -1 && (0 <= from <= 7 && 0 <= to <= 7 || 8 <= from <= 15 && 8 <= to <= 15
            || 16 <= from <= 23 && 16 <= to <= 23 || 24 <= from <= 31 && 24 <= to <= 31 || 32 <= from <= 39 && 32 <= to <= 39
            || 40 <= from <= 47 && 40 <= to <= 47 || 48 <= from <= 55 && 48 <= to <= 55
            || 56 <= from <= 63 && 56 <= to <= 63)) {
            for (int i = from - 1; i > to; i--) {
                if (currBoard_[i] != 0x20) {
                    returnType = false;
                }
            }
            returnType = true;
        }
        else if ((spaces) > 0 && (spaces) % 9 == 0) {

            for (int i = from + 9; i < to; i += 9) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if ((spaces) < 0 && (spaces) % 9 == 0) {
            for (int i = from - 9; i > to; i -= 9) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if ((spaces) > 0 && (spaces) % 7 == 0) {

            for (int i = from + 7; i < to; i += 7) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
        else if ((spaces) < 0 && (spaces) % 7 == 0) {
            for (int i = from - 7; i > to; i -= 7) {
                if (currBoard_[i] != 0x20) {
                    return false;
                }
            }
            returnType = true;
        }
    }
    else {
        returnType = true;
    }
    return returnType;
}

// this is where the murder happens, and castling gotta protect the king after all
bool Board::validateMove() {
    Pieces p;
    int spaces = to - from;
    if (p.checkLegitMove(from, to, currBoard_) && Board::traverseCell(piece, to, from)) {
        if ((piece >= 'A' && 'Z' >= piece) && (pieceTo >= 'a' && 'z' >= pieceTo) && pieceTo != 'k') {
            return true;
        }
        else if ((piece >= 'a' && 'z' >= piece) && (pieceTo >= 'A' && 'Z' >= pieceTo) && pieceTo != 'K') {

            return true;
        }
        else if (pieceTo == 0x20) {
            if (piece == 'k' && spaces == 2) {
                currBoard_[61] = currBoard_[63];
                currBoard_[63] = 0x20;
            }
            else if (piece == 'k' && spaces == -2) {
                currBoard_[58] = currBoard_[56];
                currBoard_[56] = 0x20;
            }
            else if (piece == 'K' && spaces == 2) {
                currBoard_[5] = currBoard_[7];
                currBoard_[7] = 0x20;
            }
            else if (piece == 'K' && spaces == -2) {
                currBoard_[3] = currBoard_[0];
                currBoard_[0] = 0x20;
            }
            else {
                return true;
            }
        }

        else {
            return false;
        }
    }
}

std::vector<int> Board::getAllWhiteMoves() {
    Pieces p;
    std::vector<int> allwhitemoves;
    //searchers all white pieces (r, n, b, q) and stores possbile movements in vector allwhitemoves
    for (int from = 0; from < 64; from++) {
        if (currBoard_[from] == 'R' || currBoard_[from] == 'N' || currBoard_[from] == 'B' || currBoard_[from] == 'Q') {
            for (int to = 0; to < 64; to++) {
                if (p.checkLegitMove(from, to, currBoard_) && Board::traverseCell(currBoard_[from], to, from)) {
                    if (((currBoard_[from] >= 'A' && 'Z' >= currBoard_[from]) && 
                        (currBoard_[to] >= 'a' && 'z' >= currBoard_[to])) || ((currBoard_[from] >= 'a' && 'z' >= currBoard_[from])
                        && (currBoard_[to] >= 'A' && 'Z' >= currBoard_[to])) || (currBoard_[to] == 0x20)) {
                        allwhitemoves.push_back(to);
                    }
                }
            }
        }
        //searchers all white pawns attcks and stores possbile movements in vector allwhitemoves
        else if (currBoard_[from] == 'P') {
            if (p.columnNumber(from) == 1 && (from + 9 != 'R' || from + 9 != 'N' || from + 9 != 'B' || from + 9 != 'K'
                || from + 9 != 'Q' || from + 9 != 'P')) {
                allwhitemoves.push_back(from + 9);
            }
            else if (p.columnNumber(from) == 8 && (from + 7 != 'R' || from + 7 != 'N' || from + 7 != 'B' || from + 7 != 'K' 
                || from + 7 != 'Q' || from + 7 != 'P')) {
                allwhitemoves.push_back(from + 7);
            }
            else if ((from + 7 != 'R' || from + 7 != 'N' || from + 7 != 'B' || from + 7 != 'K' || from + 7 != 'Q' || from + 7 != 'P') 
                && (from + 9 != 'R' || from + 9 != 'N' || from + 9 != 'B' || from + 9 != 'K' || from + 9 != 'Q' || from + 9 != 'P')) {
                allwhitemoves.push_back(from + 9);
                allwhitemoves.push_back(from + 7);
            }
        }
    }
    return allwhitemoves;
}

std::vector<int> Board::getAllBlackMoves() {
    Pieces p;
    std::vector<int> allblackmoves;
    //searchers all black pieces (R, N, B, Q) and stores possbile movements in vector allblackmoves
    for (int from = 63; from >= 0; from--) {
        if (currBoard_[from] == 'r' || currBoard_[from] == 'n' || currBoard_[from] == 'b' || currBoard_[from] == 'q') {
            for (int to = 63; to >= 0; to--) {
                if (p.checkLegitMove(from, to, currBoard_) && Board::traverseCell(currBoard_[from], to, from)) {
                    if (((currBoard_[from] >= 'A' && 'Z' >= currBoard_[from]) && (currBoard_[to] >= 'a' && 'z' >= currBoard_[to])) 
                        || ((currBoard_[from] >= 'a' && 'z' >= currBoard_[from])
                        && (currBoard_[to] >= 'A' && 'Z' >= currBoard_[to])) || (currBoard_[to] == 0x20)) {
                        allblackmoves.push_back(to);
                    }
                }
            }
        }
        //searchers all black pawns attcks and stores possbile movements in vector allblackmoves
        else if (currBoard_[from] == 'p') {
            if (p.columnNumber(from) == 1 && (from - 9 != 'r' || from - 9 != 'n' || from - 9 != 'b' || from - 9 != 'k' 
                || from - 9 != 'q' || from - 9 != 'p')) {
                allblackmoves.push_back(from - 9);
            }
            else if (p.columnNumber(from) == 8 && (from - 7 != 'r' || from - 7 != 'n' || from - 7 != 'b' || from - 7 != 'k'
                || from - 7 != 'q' || from - 7 != 'p')) {
                allblackmoves.push_back(from - 7);
            }
            else if ((from - 7 != 'r' || from - 7 != 'n' || from - 7 != 'b' || from - 7 != 'k' || from - 7 != 'q' || from - 7 != 'p') 
                && (from - 9 != 'r' || from - 9 != 'n' || from - 9 != 'b' || from - 9 != 'k' || from - 9 != 'q' || from - 9 != 'p')) {
                allblackmoves.push_back(from - 9);
                allblackmoves.push_back(from - 7);
            }
        }
    }
    return allblackmoves;
}

bool Board::checkBoardStatus() {
    char king;
    int checkmate = 0;
    bool check = false;
    int test = 20;
    std::string turn = "";
    int indexKing = 0;
    Pieces p;

    std::vector<int> AllMovesBlack;
    std::vector<int> AllMovesWhite;
    std::vector<int> KingMoves;

    //sets variables depending on turn
    if (counter_ % 2 != 0 && whiteTurn() == true) {
        king = 'K';
        turn = "Black";
        AllMovesBlack = Board::getAllBlackMoves();
    }
    else {
        king = 'k';
        turn = "White";
        AllMovesWhite = Board::getAllWhiteMoves();
    }

    for (int i = 0; i < 64; i++) {
        if (currBoard_[i] == king) {
            indexKing = i;
        }
    }
    //searches for king and stores all king movements in KingMoves vector
    for (int to = 0; to < 64; to++) {
        if (p.checkLegitMove(indexKing, to, currBoard_) && Board::traverseCell(king, to, indexKing)) {
            if (((king >= 'A' && 'Z' >= king) && (currBoard_[to] >= 'a' && 'z' >= currBoard_[to])) || ((king >= 'a' && 'z' >= king)
                && (currBoard_[to] >= 'A' && 'Z' >= currBoard_[to])) || (currBoard_[to] == 0x20)) {
                KingMoves.push_back(to);
            }
        }
    }

    //Black Pieces & White King
    if (turn == "Black") {
        for (int i = 0; i < AllMovesBlack.size(); i++) {
            //if indexKing equals black pieces moves, then check eqauls true and cout "White is in check!"
            if (indexKing == AllMovesBlack[i]) {
                std::cout << "White is in check!" << std::endl;
                check = true;
            }
            //if KingMoves and AllMovesBlack eqauls, then add 1 to checkmate, if checkmate eqauls KingMoves.size
           //and check eqauls true then return true and cout "White is in checkmate! Black Wins!" 
            for (int x = 0; x < KingMoves.size(); x++) {
                if (KingMoves[x] == AllMovesBlack[i] && AllMovesBlack[i] != 0) {
                    checkmate++;
                    if (KingMoves.size() == checkmate && check == true) {
                        std::cout << "White is in checkmate! " << turn << " Wins!" << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    //White Pieces & Black King
    else {
        for (int i = 0; i < AllMovesWhite.size(); i++) {
            //if indexKing equals white pieces moves, then check eqauls true and cout "Black is in check!"
            if (indexKing == AllMovesWhite[i]) {
                std::cout << "Black is in check!" << std::endl;
                check = true;
            }
            //if KingMoves and AllMovesWhite eqauls, then add 1 to checkmate, if checkmate eqauls KingMoves.size
           //and check eqauls true then return true and cout "Black is in checkmate! White Wins!" 
            for (int x = 0; x < KingMoves.size(); x++) {
                if (KingMoves[x] == AllMovesWhite[i] && AllMovesWhite[i] != 0) {
                    checkmate++;
                    if (KingMoves.size() == checkmate && check == true) {
                        std::cout << "Black is in checkmate! " << turn << " Wins!" << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    //return false, if statement didn't return true
    return false;
}
