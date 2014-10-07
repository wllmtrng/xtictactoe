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
// Board.C
/////////////////////////////////////////////////////////////
#include "Board.h"

// Array of all possible winning patterns. 1 indicates a win

int Board::winningBits_[8][9] = {
{ 1, 0, 0, 1, 0, 0, 1, 0, 0 },
{ 0, 1, 0, 0, 1, 0, 0, 1, 0 },
{ 0, 0, 1, 0, 0, 1, 0, 0, 1 },
{ 1, 1, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 0, 0, 1, 0, 1, 0, 1, 0, 0 },
};

Board::Board()
{
    clear();  // Initialize the board
}

void Board::clear()
{
    // NOBODYYET doubles as an indication that no one has won
    // and that no move has been recorded for a square

    for ( int i = 0; i < 9; i++ ) {
      state_[i] = NOBODYYET;
    }
}

Board::MoveStatus Board::recordMove (int position, Board::markType mark)
{
    if (state_[position] != NOBODYYET ) { // Make sure square is empty
      return kIllegalMove;
    }

    // Record the move, and report it as legal
    state_[position] = mark;
    return kValidMove;
}

int *const Board::freeSquares ( int &numFree )
{
  int i, j;

  // Build up a list of the indexes (0-8) of free squares

  for ( j = 0, i = 0; i < 9; i++ ) {
    if (state_[i] == NOBODYYET) {
      freeList_[j++] = i;
    }
  }

  numFree = j;
  return freeList_;
}

int Board::numFreeSquares()
{
  int i, count;

  // Look for and count unmarked squares
  for ( count = 0, i = 0; i < 9; i++ ) {
    if (state_[i] == NOBODYYET ) {
      count++;
    }
  }

  return count;
}

Board::markType Board::whoHasWon()
{
  int i, j;

  // Check the state of the board to see if anyone has won
  for ( i = 0; i < 8; i++ ) {
    int xcount = 0;  // Initialize to no X's, no O's
    int ocount = 0;

    winningPattern_ = winningBits_[i];   // Remember in case of a win

    for ( j = 0; j < 9; j++ ) {     // Test each winning pattern
      if (winningBits_[i][j]) {
        if (state_[j] == OO ) {
          ocount++;          // Count O's in winning squares
        }
        else if (state_[j] == XX ) {
          xcount++;          // Count X's in winning squares
        }
      }
    }

    if ( ocount == 3 ) {   // If either mark occupied 3 squares
      return OO;       // then return the winner
    }
    if ( xcount == 3 ) {
        return XX;
    }
  }

    if ( numFreeSquares() > 0 ) {  // If no one won, report a tie or
      return NOBODYYET;        // continue the game, as appropriate
    }
    else {
      return TIE;
    }
}
