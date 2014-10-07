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

///////////////////////////////////////////////////////////////////////////////
//
// The following code has been modified slightly to match my coding style
// - William Truong
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////
// MoveGenerator.C
//////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>

#include "unistd.h"

#include "MoveGenerator.h"
#include "Board.h"



MoveGenerator::MoveGenerator()
{
    srand48( (long) getpid() );
}

int MoveGenerator::getNextMove (Board* board)
{
    int randomIndex, movesLeft;
    // Get the list of free squares on the Board
    int* const freeSquares = board->freeSquares(movesLeft);

    if ( movesLeft == 0 ) {
      return -1;
    }

    // Pick one of the free squares at random and return it
    randomIndex = (int) ( movesLeft * drand48() );

    return freeSquares[randomIndex];
}
