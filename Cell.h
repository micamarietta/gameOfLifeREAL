#ifndef __Cell_h__
#define __Cell_h__
#include <iostream>
using namespace std;

class Cell{
  private:
    string gameMode;
    int myRow = 0;
    int myColumn = 0;
    bool curIsAlive;
    bool nextIsAlive;

    void classicThriveOrDie(Cell *** grid, int numRows, int numColumns);
    void mirrorThriveOrDie(Cell *** grid, int numRows, int numColumns);
    void donutThriveOrDie(Cell *** grid, int numRows, int numColumns, int rowToCheck, int colToCheck);

  public:
    Cell(int row, int column);
    void thriveOrDie(string mode, Cell *** grid, int numRows, int numColumns);
    void applyChanges();
    char cellToString();

    void setCurIsAlive(bool value) {
      curIsAlive = value;
    }

    bool getCurIsAlive() {
      return curIsAlive;
    }

    void setNextIsAlive(bool value) {
      nextIsAlive = value;
    }

    bool getNextIsAlive() {
      return nextIsAlive;
    }
};
#endif
