/*
 * Engine.h
 *
 *  Created on: Oct 6, 2014
 *      Author: wtruong-local
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Board.h"

class TicTacToe;
class MoveGenerator;

class Engine
{
  protected:
    TicTacToe*       game_;
    Board::markType  whoseMove_;     // Remember whose turn it is
    Board*           board_;         // Internal game state
    MoveGenerator*   moveGenerator_; // Picks next move
    int              gameOver_;      // True is game has ended
    void   checkForWin();            // Check and report the winner
  public:
    Engine ( TicTacToe * );
    virtual ~Engine();
    void recordMove ( int square );
    void reset();                    // Start over
    void quit();
    virtual const char *const className() { return "Engine"; }
};
#endif /* ENGINE_H_ */
