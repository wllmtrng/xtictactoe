/*
 * Command.h
 *
 *  Created on: Oct 6, 2014
 *      Author: wtruong-local
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "UIComponent.h"

class TicTacToe;

class Command: public UIComponent
{
  private:
    static void newGameCallback ( Widget, XtPointer, XtPointer );
    static void quitCallback ( Widget, XtPointer, XtPointer );

  protected:
    Widget     newGame_;
    Widget     quit_;
    TicTacToe *game_;
    virtual void newGame();
    virtual void quit();

  public:
    Command(const std::string&, Widget, TicTacToe*);
    virtual const char * const className() { return "Command"; };
};

#endif /* COMMAND_H_ */
