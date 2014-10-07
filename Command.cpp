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
// Command.C: Manage a set of command buttons
/////////////////////////////////////////////////////////
#include "stdlib.h"
#include "TicTacToe.h"
#include "Command.h"
#include "Engine.h"
#include <Xm/Form.h>
#include <Xm/PushB.h>

Command::Command(const std::string& name,
                 Widget             parent,
                 TicTacToe *game) : UIComponent(name)
{
  game_ = game;

  // Set up an XmForm widget to manage the buttons
  w_ = XmCreateForm ( parent, const_cast<char*>(name_.c_str()), NULL, 0);
  installDestroyHandler();
  // Create the command buttons and attach callbacks
  newGame_ =
      XtVaCreateManagedWidget ( "newGame",
       xmPushButtonWidgetClass, w_,
       XmNtopOffset,        5,
       XmNbottomOffset,     5,
       XmNleftOffset,       5,
       XmNtopAttachment,    XmATTACH_FORM,
       XmNleftAttachment,   XmATTACH_FORM,
       XmNrightAttachment,  XmATTACH_NONE,
       XmNbottomAttachment, XmATTACH_FORM,
       NULL );

  quit_ =
      XtVaCreateManagedWidget ( "quit",
       xmPushButtonWidgetClass, w_,
       XmNtopOffset,        5,
       XmNbottomOffset,     5,
       XmNrightOffset,      5,
       XmNtopAttachment,    XmATTACH_FORM,
       XmNleftAttachment,   XmATTACH_NONE,
       XmNrightAttachment,  XmATTACH_FORM,
       XmNbottomAttachment, XmATTACH_FORM,
       NULL );

  XtAddCallback (newGame_,
                 XmNactivateCallback,
                 &Command::newGameCallback,
                 (XtPointer) this );

  XtAddCallback (quit_,
                 XmNactivateCallback,
                 &Command::quitCallback,
                 (XtPointer) this );
}

void Command::newGameCallback (Widget,
			                         XtPointer clientData,
			                         XtPointer)
{
    Command *obj = (Command *) clientData;
    obj->newGame();
}

void Command::newGame()
{
    game_->engine()->reset();
}

void Command::quitCallback ( Widget,
			    XtPointer clientData,
			    XtPointer )
{
  Command *obj = (Command *) clientData;
  obj->quit();
}

void Command::quit()
{
  game_->engine()->quit();
}
