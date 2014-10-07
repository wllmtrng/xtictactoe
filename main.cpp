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
// tictactoe.C: A simple tic-tac-toe game using Motif and C++
/////////////////////////////////////////////////////////////
#include <Xm/Xm.h>
#include "TicTacToe.h"

int main(int argc, char **argv)
{
  XtAppContext app;
  Widget toplevel;

  // Initialize the Intrinsics
  toplevel = XtAppInitialize(&app, "Tictactoe", NULL, 0, &argc, argv, NULL,
      NULL, 0);

  // Create the game widget tree as a child of the shell widget
  TicTacToe *game = new TicTacToe("game", toplevel);

  game->manage();
  // Realize all widgets and enter the event loop
  XtRealizeWidget(toplevel);
  XtAppMainLoop(app);
}
