///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//         This example code is from the book:
//
//           Object-Oriented Programming with C++ and OSF/Motif
//         by
//           Douglas Young
//           Prentice Hall, 1992
//           ISBN 0-13-630252-1
//
//         Copyright 1991 by Prentice Hall
//         All Rights Reserved
//
//  Permission to use, copy, modify, and distribute this software for
//  any purpose except publication and without fee is hereby granted, provided
//  that the above copyright notice appear in all copies of the software.
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
// Board.h: Represent a tictactoe board
/////////////////////////////////////////////////////////////
#ifndef BOARD_H
#define BOARD_H

// Convenient values
class Board {

  protected:

    int  state_[9];        // Internal game state
    int  freeList_[9];     // List used to report free squares
    int  numFreeSquares();
    int* winningPattern_; // Pattern last tested when someone wins
    static int winningBits_[8][9];

  public:
    enum MoveStatus {kValidMove, kIllegalMove };
    enum markType {NOBODYYET, OO, XX, TIE };

    Board();
    // Record an X or an O
    MoveStatus recordMove (int, markType );

    // Return number of available squares, and their indexes
    int *const freeSquares ( int& );

    // Public access for winning pattern of squares
    int *const winningSquares() { return winningPattern_; }

    void clear();           // Clear and reset the board
    markType whoHasWon();   // Return code for possible winner
    const char *const className() { return "Board"; }
};
#endif
