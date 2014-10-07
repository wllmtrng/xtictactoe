/*
 * GameBoard.h
 *
 *  Created on: Oct 4, 2014
 *      Author: wtruong
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "UIComponent.h"
#include "TicTacToe.h"

class GameBoard: public UIComponent
{
  public:
    GameBoard(const std::string&, Widget, TicTacToe* const);
    virtual ~GameBoard();
    void highlightSquare(int square);  // Highlight single square
    void deemphasizeSquare(int square); // Fade square to 2D
    void activateSquare(int square); // Allow input to square
    void deactivateSquare(int square); //Shut off input
    virtual void markO(int square); //Put an O in the square
    virtual void markX(int square); //Put an X in the square
    void clear();                   //Clear and reset the board
    virtual const char* const className() {return "GameBoard";}
  protected:
    Widget           grid_[9];         // 3 x 3 square of buttons
    GC               gc_;
    int              gridSize_;        // Size of each square
    TicTacToe* const game_;
    Pixel            highlightColor_;  // Color of border when in active square
    Pixel            noHighlightColor_;// Border color of inactive squares
    Dimension        shadowThickness_; // Default shadow width of a square

    // Methods for refreshing the squares and getting input
    virtual void drawX(Widget);
    virtual void drawO(Widget);

  private:
    void mark(int); //Handle user marking a square
    // Callbacks registered with widgets in the grid
    static void markCallback(Widget, XtPointer, XtPointer);
    static void drawXCallback(Widget, XtPointer, XtPointer);
    static void drawOCallback(Widget, XtPointer, XtPointer);
};

#endif /* GAMEBOARD_H_ */
