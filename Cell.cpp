#include "Cell.h"

Cell::Cell(int row, int column){
  myRow = row;
  myColumn = column;
}


//determine whether the cell will be alive or dead in the next generation
//refers to different functions for each game mode
void Cell::thriveOrDie(string mode, Cell *** grid, int numRows, int numColumns){
  //cout << "ToD on cell [" << numRows << "][" << numColumns << "]..." << endl;

  if(mode =="Classic"){
    // perform classic thrive or die
    classicThriveOrDie(grid,numRows,numColumns);
  }
  else if(mode =="Mirror"){
    //cout << "ToD Mirror" << endl;
    //performs mirror thrive or die
    mirrorThriveOrDie(grid,numRows,numColumns);

  }
  else if(mode =="Donut"){
    //performs donut thrive or die
    //cout << "ToD Donut" << endl;
    int rowToCheck = 0;
    int colToCheck = 0;
    donutThriveOrDie(grid,numRows,numColumns, rowToCheck, colToCheck);
  }
  else{
    // throw error if the mode isn't one of the three
    cout << "ERROR - unhandled mode" << endl;
  }
}

//------------------------ THRIVE OR DIE GAME MODES ---------------------------

//classic version of thrive or die
void Cell::classicThriveOrDie(Cell *** grid, int numRows, int numColumns){
  // count how many neighbors are alive
  int numOfAliveNeighbors = 0;
  //cout << "ToD on cell [" << myRow << "][" << myColumn << "]..." << endl;
  //cout << "     numRows: " << numRows << ", numColumns: " << numColumns << endl;
  for(int i = myRow - 1; i <= myRow + 1; ++i){
    //if the index of the row is less than 0 or greater than the upper bound, ignore it
    if (i < 0 || i > numRows-1){
      //cout << "     skipping row " << i << endl;
      continue;
    }

    for(int j = myColumn - 1; j <= myColumn + 1; ++j){
      //if the index of the column is less than 0 or greater than the upper bound, ignore it
      //it will not be in the possible range for neighbors in this mode
      if (j < 0 || j > numColumns - 1){
        //cout << "     skipping col " << j << endl;
        continue;
      }

      //skip myself
      if (i == myRow && j == myColumn){
        //cout << "     skipping myself " << endl;
        continue;
      }

      bool neighborIsAlive = grid[i][j]->getCurIsAlive();
      //cout << "     neighbor cell [" << i << "][" << j <<"] is " << neighborIsAlive << endl;
      if(neighborIsAlive){
        ++numOfAliveNeighbors;
      }
    }
  }

  //based on num of neighbors, determine if the cell will live or die
  if(numOfAliveNeighbors <= 1 || numOfAliveNeighbors >= 4){
    nextIsAlive = false;
  } else if(numOfAliveNeighbors == 3){
    nextIsAlive = true;
  } else if (numOfAliveNeighbors == 2){
    nextIsAlive = curIsAlive;
  }

  //cout << "     [" << myRow << "][" << myColumn << "] : " << numOfAliveNeighbors << " neighbors, nextIsAlive = " << nextIsAlive << endl;
}

void Cell::donutThriveOrDie(Cell *** grid, int numRows, int numColumns, int rowToCheck, int colToCheck){
  // count how many neighbors are alive
  int numOfAliveNeighbors = 0;

  // int rowToCheck = 0;
  // int colToCheck = 0;
  //cout << "ToD on cell [" << myRow << "][" << myColumn << "]..." << endl;
  //cout << "     numRows: " << numRows << ", numColumns: " << numColumns << endl;
  //cout << "coltocheck: " << colToCheck << endl;
  //cout << "rowtocheck: " << rowToCheck << endl;

  for(int i = myRow - 1; i <= myRow + 1; ++i){
    //if the index of the row is less than 0 or greater than the upper bound, then we are dealing with the far left and far right edges + corners
    //cout << "does this cout? " << endl;
    //if (i < 0 || i > numRows-1){

      //set the row to check

      //ERROR: rows on the inside think that i < 0 instead of i = numRows
      if(i < 0){
        //row not in range (above)
        //cout << "row to check = " << numRows - 1 << endl;
        rowToCheck = numRows - 1;
      }
      else if(i == numRows){
        //row not in range (below)
        //cout << "row not in range below " << endl;
        rowToCheck = 0;
      }
      else{
        //row in range
        //cout << "executing this row in range section " << endl;
        rowToCheck = i;
      }
    //}

    //loop through columns
    for(int j = myColumn - 1; j <= myColumn + 1; ++j){

        if (j < 0){
          //column not in range (left)
          colToCheck = numColumns - 1;


        }
        else if(j == numColumns){
          //column not in range (right)
          colToCheck = 0;
        }
        else{
          //column in range
          colToCheck = j;
        }

        //skip myself
        if (i == myRow && j == myColumn){
          continue;
        }
        //cout << "rowToChec: " << rowToCheck << endl;

        //cout << "colToChec: " << colToCheck << endl;

        bool neighborIsAlive = grid[rowToCheck][colToCheck]->getCurIsAlive();
        //cout << "coltocheck: " << colToCheck << endl;
        //cout << "checking if the row to check : " << rowToCheck <<  " and col to check :" << colToCheck << " are out of bounds" << endl;
        if(neighborIsAlive){
          ++numOfAliveNeighbors;
        }
      }
    }


    //bool neighborIsAlive = grid[i][j]->getCurIsAlive();
    //cout << "     neighbor cell [" << i << "][" << j <<"] is " << neighborIsAlive << endl;


    //based on num of neighbors, determine if the cell will live or die
    if(numOfAliveNeighbors <= 1 || numOfAliveNeighbors >= 4){
      nextIsAlive = false;
    } else if(numOfAliveNeighbors == 3){
      nextIsAlive = true;
    } else if (numOfAliveNeighbors == 2){
      nextIsAlive = curIsAlive;
    }
}

void Cell::mirrorThriveOrDie(Cell *** grid, int numRows, int numColumns){
  //count number of neighbors that are alive
  int numOfAliveNeighbors = 0;
  bool neighborIsAlive;

  for(int i = myRow - 1; i <= myRow + 1; ++i){

    for(int j = myColumn - 1; j <= myColumn + 1; ++j){

      //determine which indexes are corners
      //do not skip myself (reflect self, horizontally, vertically, and diagonally)
      //if i am a corner, and i am alive, add three to numNeighbors automatically

      //im on the edge and my neighbor is diagonal
      if(((i<0)&&(j<0)) || ((i<0)&&(j>=numColumns)) || ((i>=numRows)&&(j<0)) || ((i>=numRows)&&(j>=numColumns))){
        neighborIsAlive = curIsAlive;
      }

      //im on the edge and my neighbor is vertical
      else if(i < 0 && j == myColumn){
        neighborIsAlive = curIsAlive;
      }
      else if(i >= numRows && j == myColumn){
        neighborIsAlive = curIsAlive;
      }

      //im on the edge and my neighbor is horizontal
      else if(i == myRow && j < 0){
        neighborIsAlive = curIsAlive;
      }
      else if(i == myRow && j >= numColumns){
        neighborIsAlive = curIsAlive;
      }

      //top left diagonal neighbors
      else if(i < 0  && j == myColumn + 1){
        neighborIsAlive = grid[myRow][myColumn+1]->getCurIsAlive();
      }
      else if(i == myRow +1 && j < 0){
        neighborIsAlive = grid[myRow+1][myColumn]->getCurIsAlive();
      }

//top right diagonal neighbors
      else if(i < 0  && j == myColumn - 1){
        neighborIsAlive = grid[myRow][myColumn-1]->getCurIsAlive();
      }
      else if(i == myRow +1 && j >= numColumns){
        neighborIsAlive = grid[myRow+1][myColumn]->getCurIsAlive();
      }

      //bottom right diagonal neighbors
      else if(i >= numRows  && j == myColumn - 1){
        neighborIsAlive = grid[myRow][myColumn-1]->getCurIsAlive();
      }
      else if(i == myRow - 1 && j >= numColumns){
        neighborIsAlive = grid[myRow-1][myColumn]->getCurIsAlive();
      }

      //bottom left diagonal neighbors
      else if(i == myRow - 1  && j < 0){
        neighborIsAlive = grid[myRow-1][myColumn]->getCurIsAlive();
      }
      else if(i >= numRows && j == myColumn + 1){
        neighborIsAlive = grid[myRow][myColumn+1]->getCurIsAlive();
      }

      //ignore myself
      else if(i == myRow && j == myColumn){
        continue;
      }

      //inside of the grid
      else{
        neighborIsAlive = grid[i][j]->getCurIsAlive();
      }

      if(neighborIsAlive){
        ++numOfAliveNeighbors;
      }
    }
  }

  if(numOfAliveNeighbors <= 1 || numOfAliveNeighbors >= 4){
    nextIsAlive = false;
  } else if(numOfAliveNeighbors == 3){
    nextIsAlive = true;
  } else if (numOfAliveNeighbors == 2){
    nextIsAlive = curIsAlive;
  }
}

void Cell::applyChanges(){
   curIsAlive = nextIsAlive;
}
//-----------------------------------------------------------------------------

char Cell::cellToString(){
  if(curIsAlive){
    return 'X';
  } else {
    return '-';
  }
}
