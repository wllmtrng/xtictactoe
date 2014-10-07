/*
 * GameBoard.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: wtruong
 */

#include <Xm/RowColumn.h>
#include <Xm/DrawnB.h>
#include "GameBoard.h"
#include "Engine.h"

GameBoard::GameBoard(const std::string& name,
                     Widget             parent,
                     TicTacToe* const   game)
    : UIComponent(name), game_(game)
{
  XGCValues values;
  gridSize_ = 100;

  // Create an XmRowColumn widget to manage a 3x3
  // grid of widgets
  w_ = XtVaCreateWidget(name_.c_str(), xmRowColumnWidgetClass, parent,
                        XmNnumColumns, 3,
                        XmNpacking, XmPACK_COLUMN,
                        XmNorientation, XmHORIZONTAL,
                        XmNadjustLast, FALSE,
                        NULL);
  installDestroyHandler();

  // Create a grid of 9 XmDrawnButton widgets
  // Store the index of each widget's position in the grid
  // so it can be used to identify the widget's position later
  for (int i = 0; i < 9; i ++) {
    grid_[i] = XtVaCreateWidget ("xo",
                                 xmDrawnButtonWidgetClass, w_,
                                 XmNuserData, i,
                                 XmNrecomputeSize, FALSE,
                                 XmNpushButtonEnabled, TRUE,
                                 XmNshadowType, XmSHADOW_OUT,
                                 XmNwidth, gridSize_,
                                 XmNheight, gridSize_,
                                 NULL);

    // Get user input to mark a square
    XtAddCallback(grid_[i], XmNactivateCallback,
                  GameBoard::markCallback,
                  (XtPointer)this);
  }

  XtManageChildren(grid_, 9);

  // Get the background color of the rowcolumn widget,
  // to be used to effectively shut off highlight-on-enter
  XtVaGetValues(w_, XmNbackground, &noHighlightColor_, NULL);

  // Get the GC needed to display the Xs and Os
  // and retrieve and save the normal highlight color
  // Use the color of the first widget in the grid
  XtVaGetValues(grid_[0], XmNforeground,      &values.foreground,
                          XmNhighlightColor,  &highlightColor_,
                          XmNshadowThickness, &shadowThickness_,
                          NULL);
  gc_ = XtGetGC(grid_[0], GCForeground, &values);
}

GameBoard::~GameBoard()
{
  if (w_) {
    XtReleaseGC(w_, gc_);
  }
}

void GameBoard::highlightSquare(int position)
{
  // Emphasize a square by changing the shadow type
  XtVaSetValues(grid_[position],
                XmNshadowType,      XmSHADOW_ETCHED_OUT,
                XmNshadowThickness, 2 * shadowThickness_,
                NULL);
}

void GameBoard::deemphasizeSquare(int position)
{
  // Make a square fade into the background by shutting
  // off the Motif 3-d effect
  XtVaSetValues(grid_[position], XmNshadowThickness, 0, NULL);
}

void GameBoard::activateSquare(int position)
{
  // Make the button look active by setting the shadow
  // type to normal, enabling pushbutton behavior,
  // and turning on highlights when the mouse enters the square

  XtVaSetValues(grid_[position],
                XmNpushButtonEnabled, TRUE,
                XmNshadowType,        XmSHADOW_OUT,
                XmNshadowThickness,   shadowThickness_,
                XmNhighlightColor,    highlightColor_,
                NULL);
}

void GameBoard::deactivateSquare(int position)
{
  XtVaSetValues(grid_[position],
                XmNpushButtonEnabled, FALSE,
                XmNshadowType,        XmSHADOW_IN,
                XmNhighlightColor,    noHighlightColor_,
                NULL);
}

void GameBoard::markO(int position)
{
  // Remove any previous callbacks, add one to draw
  // an O and then trigger an Expose event to
  // display the O in this square
  XtRemoveAllCallbacks(grid_[position], XmNexposeCallback);
  deactivateSquare(position);
  XtAddCallback(grid_[position],
                XmNexposeCallback,
                GameBoard::drawOCallback,
                (XtPointer)this);
  if (XtIsRealized(grid_[position])) {
    XClearArea(XtDisplay(grid_[position]),
               XtWindow(grid_[position]),
               0, 0, 0, 0, TRUE);
  }
}

void GameBoard::markX(int position)
{
  // Remove any previous callbacks, add one to draw
  // an X and then trigger an Expose event to
  // display the X in this square
  XtRemoveAllCallbacks(grid_[position], XmNexposeCallback);
  deactivateSquare(position);
  XtAddCallback(grid_[position],
                XmNexposeCallback,
                GameBoard::drawXCallback,
                (XtPointer)this);
  if (XtIsRealized(grid_[position])) {
    XClearArea(XtDisplay(grid_[position]),
               XtWindow(grid_[position]),
               0, 0, 0, 0, TRUE);
  }
}

void GameBoard::clear()
{
  // Each element of the grid may have a callback for an X or an O, so all
  // callbacks must be removed
  for (int i = 0; i < 9; i++) {
    XtRemoveAllCallbacks(grid_[i], XmNexposeCallback);
    activateSquare(i);

    // Use XClearArea with exposure events requested
    // so that the widget's shadow is redrawn
    if (XtIsRealized(grid_[i])) {
      XClearArea(XtDisplay(grid_[i]),
                 XtWindow(grid_[i]),
                 0, 0, 0, 0, TRUE);
    }
  }
}

void GameBoard::drawX(Widget square)
{
  // Draw the X across the widget
  int left   = (int)(0.2 * gridSize_);
  int top    = (int)(0.2 * gridSize_);
  int right  = (int)(0.8 * gridSize_);
  int bottom = (int)(0.8 * gridSize_);

  XDrawLine(XtDisplay(square), XtWindow(square),
            gc_, left, top, right, bottom);
  XDrawLine(XtDisplay(square), XtWindow(square),
            gc_, right, top, left, bottom);
}

void GameBoard::drawO(Widget square)
{
  // Draw the O across the widget
  int left   = (int)(0.2 * gridSize_);
  int top    = (int)(0.2 * gridSize_);
  int width  = (int)(0.6 * gridSize_);
  int height = (int)(0.6 * gridSize_);

  XDrawArc(XtDisplay(square), XtWindow(square),
            gc_, left, top, width, height, 0, 360 * 64);
}

void GameBoard::mark(int index)
{
  game_->engine()->recordMove(index);
}

void GameBoard::markCallback(Widget w, XtPointer clientData, XtPointer)
{
  int index;

  GameBoard *obj = (GameBoard*)clientData;
  XtVaGetValues(w, XmNuserData, &index, NULL);
  obj->mark(index);
}

void GameBoard::drawXCallback(Widget w, XtPointer clientData, XtPointer)
{
  // Retrieve the GameBoard object
  GameBoard *obj = (GameBoard*)clientData;
  obj->drawX(w);
}

void GameBoard::drawOCallback(Widget w, XtPointer clientData, XtPointer)
{
  // Retrieve the GameBoard object
  GameBoard *obj = (GameBoard*)clientData;
  obj->drawO(w);
}
