/*
 * TicTacToe.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: wtruong
 */

#include "Xm/Form.h"
#include "Xm/Separator.h"

#include "TicTacToe.h"
#include "GameBoard.h"
#include "Engine.h"
#include "Message.h"
#include "Command.h"

TicTacToe::TicTacToe(const std::string& name, Widget parent)
    : UIComponent(name)
{
  // Create driving engine for the game
  engine_ = new Engine(this);
  // Create a form to hold all other widgets
  w_ = XtCreateWidget(name_.c_str(), xmFormWidgetClass, parent, NULL, 0);
  installDestroyHandler();

  // Separate the commands from the message area
  Widget sep = XtCreateManagedWidget("commandSeparator",
                                     xmSeparatorWidgetClass,
                                     w_, NULL, 0);
  // Create the widgets for the UI Components
  msgArea_ = new Message("messages", w_);
  cmdArea_ = new Command("commands", w_, this);
  gameBoard_ = new GameBoard("gameBoard", w_, this);

  //Set up all constraints

  // The Gameboard is attached to the parent XmForm widget
  // on the top and sides; to an XmSeparator on the bottom
  XtVaSetValues(gameBoard_->baseWidget(),
                XmNtopAttachment,    XmATTACH_FORM,
                XmNleftAttachment,   XmATTACH_FORM,
                XmNrightAttachment,  XmATTACH_FORM,
                XmNbottomWidget,     sep,
                XmNbottomAttachment, XmATTACH_WIDGET,
                NULL);
  // Attach a separator widget to the top of the message area
  XtVaSetValues(sep,
                XmNtopAttachment,    XmATTACH_NONE,
                XmNleftAttachment,   XmATTACH_FORM,
                XmNrightAttachment,  XmATTACH_FORM,
                XmNbottomWidget,     msgArea_->baseWidget(),
                XmNbottomAttachment, XmATTACH_WIDGET,
                NULL);
  // Attach the Message component to the separator,
  // and span the width of the Form widget
  XtVaSetValues(msgArea_->baseWidget(),
                XmNtopAttachment,    XmATTACH_NONE,
                XmNleftAttachment,   XmATTACH_FORM,
                XmNrightAttachment,  XmATTACH_FORM,
                XmNbottomWidget,     cmdArea_->baseWidget(),
                XmNbottomAttachment, XmATTACH_WIDGET,
                NULL);
  // Attach the Command component to the top, left, and right
  // sides of the form, so it floats along the top
  XtVaSetValues(cmdArea_->baseWidget(),
                XmNtopAttachment,    XmATTACH_NONE,
                XmNleftAttachment,   XmATTACH_FORM,
                XmNrightAttachment,  XmATTACH_FORM,
                XmNbottomAttachment, XmATTACH_FORM,
                NULL);

  // Manage the widgets for all subcomponents, so that managing
  // the TicTacToe base widget display everything
  cmdArea_->manage();
  gameBoard_->manage();
  msgArea_->manage();
  gameBoard_->clear();
}

