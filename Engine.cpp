/////////////////////////////////////////////////////////
// Engine.C: The brains of the tic-tac-toe game
/////////////////////////////////////////////////////////
#include "TicTacToe.h"
#include "Engine.h"
#include "GameBoard.h"
#include "MoveGenerator.h"
#include "Message.h"
#include "Board.h"
#include <stdlib.h>  // Needed for exit()

static const std::string NEWGAMEMSG     = "New Game. Choose an X square";
static const std::string ILLEGALMOVEMSG = "Illegal Move, Choose an other X square";
static const std::string USERSMOVEMSG   = "Choose an X square";
static const std::string XWINSMSG       = "X Wins!";
static const std::string OWINSMSG       = "O Wins!";
static const std::string TIEGAMEMSG     = "Tie Game";
static const std::string GAMEISOVERMSG  = "Sorry, the game is over";

Engine::Engine (TicTacToe* game)
{
    game_      = game;
    gameOver_  = FALSE;
    whoseMove_ = Board::XX;  // Start with X as the first move
    board_ =     new Board(); // Create the Engine subcomponents
    moveGenerator_ = new MoveGenerator();
}

Engine::~Engine()
{
    delete board_;
    delete moveGenerator_;
}

void Engine::reset()
{
    whoseMove_ = Board::XX;
    gameOver_  = FALSE;
    board_->clear();
    game_->gameBoard()->clear();
    game_->messageArea()->postMessage(NEWGAMEMSG);
}

void Engine::recordMove (int position)
{
  //Don't accept moves if game is over
  if (gameOver_) {
    game_->messageArea()->postAlert(GAMEISOVERMSG);
    return;
  }

  // Record the move. If it is valid, display it on the board
  // Otherwise ask the user to pick again.
  if (board_->recordMove(position, whoseMove_) == Board::kValidMove)
  {
    if(whoseMove_ == Board::XX) {
      game_->gameBoard()->markX ( position );
    }
    else {
      game_->gameBoard()->markO ( position );
    }
  }
  else
  {
    game_->messageArea()->postAlert(ILLEGALMOVEMSG);
    return;
  }

    // See if this move wins the game for the user

    checkForWin();

    if (gameOver_) {
      return;
    }

    // If this is the game's move, change to X's move and ask the
    // user to choose a square. If it is the user's move, change to
    // our move and pick a move. Call this function
    // recursively to record the game's choice.

    if (whoseMove_ == Board::OO)
    {
      whoseMove_ = Board::XX;
      game_->messageArea()->postMessage ( USERSMOVEMSG );
    }
    else
    {
      whoseMove_ = Board::OO;
      recordMove (moveGenerator_->getNextMove(board_));
    }
}

void Engine::checkForWin()
{
  int             i;
  int*            winningSquares;
  Board::markType winner;

  // If no one has won yet, just keep playing
  if ((winner = board_->whoHasWon()) == Board::NOBODYYET ) {
    return;
  }
  else if (winner == Board::TIE)
  {
    // It's a tie, end the game and notify the user
    gameOver_ = TRUE;

    for ( i = 0 ; i < 9; i++ ) {
        game_->gameBoard()->deemphasizeSquare(i);
    }

    game_->messageArea()->postAlert( TIEGAMEMSG );
  }
  else {
    // Somebody won
    gameOver_ = TRUE;

    // Get the mask for the wining pattern
    winningSquares = board_->winningSquares();

    // Deactivate each square to prevent input. Highlight
    // the winning squares, and fade others into the background.
    for ( i = 0 ; i < 9; i++ )
    {
      game_->gameBoard()->deactivateSquare ( i );

      if (winningSquares[i]) {
        game_->gameBoard()->highlightSquare ( i );
      }
      else {
        game_->gameBoard()->deemphasizeSquare ( i );
      }
    }

    // Finally, alert the user that someone has won
    if ( winner  == Board::XX ) {
      game_->messageArea()->postAlert (XWINSMSG);
    }
    else {
      game_->messageArea()->postAlert (OWINSMSG);
    }
  }
}

void Engine::quit()
{
    exit ( 0 );
}
