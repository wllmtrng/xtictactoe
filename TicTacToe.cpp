/*
 * TicTacToe.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: wtruong
 */

#include "TicTacToe.h"
#include "GameBoard.h"

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
  cmdArea_ = new Command("commands", w_);
  gameBoard_ = new GameBoard("gameBoard", w_);

  //Set up all constraints

  // The Gameboard is attached to the parent XmForm widget
  // on the top and sides; to an XmSeparator on the bottom
  XtVaSetValues(gameboard_->baseWidget(),
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
                XmNbottomWidget,     sep,
                XmNbottomAttachment, XmATTACH_WIDGET,
                NULL);
  // Attach the Message component to the separator,
  // and span the width of the Form widget
  XtVaSetValues(msgArea->baseWidget(),
                XmNtopAttachment,    XmATTACH_NONE,
                XmNleftAttachment,   XmATTACH_FORM,
                XmNrightAttachment,  XmATTACH_FORM,
                XmNbottomAttachment, cmdArea_->baseWidget(),
                NULL);
  // Attach the Command component to the top, left, and right
  // sides of the form, so it floats along the top
  XtVaSetValues(msgArea->baseWidget(),
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


