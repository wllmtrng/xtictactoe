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


/////////////////////////////////////////////////////////
// MoveGenerator.h: Pick a move for TicTacToe
////////////////////////////////////////////////////////
#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H
class Board;

class MoveGenerator {

  public:

    MoveGenerator();
    int getNextMove(Board *board);  // Determine a good move
    const char *const className() { return "MoveGenerator"; }
};
#endif

