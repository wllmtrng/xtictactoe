/*
 * TicTacToe.h
 *
 *  Created on: Oct 4, 2014
 *      Author: wtruong
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include <string>

#include "UIComponent.h"

class GameBoard;
class Message;
class Command;
class Engine;

class TicTacToe: public UIComponent
{
    friend GameBoard;
    friend Command;
    friend Engine;

  public:
    TicTacToe(const std::string&, Widget);
    virtual ~TicTacToe(){};
    virtual const char* const className() {return "TicTacToe";}

  protected:
    GameBoard* gameBoard() const {return gameBoard_;}
    Message* messageArea() const {return msgArea_;}
    Command* commandArea() const {return cmdArea_;}
    Engine* engine() const {return engine_;}

  private:
    GameBoard* gameBoard_;
    Message* msgArea_;
    Command* cmdArea_;
    Engine* engine_;
};

#endif /* TICTACTOE_H_ */
