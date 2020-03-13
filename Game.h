#include <iostream>
#include "Cell.h"
using namespace std;

class Game{

public:

  Game(); //ctor
  void start(); //calls entire game

private:
  string gameMode;
  //functions
  //creates a grid
  static Cell *** generateGrid(int row, int column);

  //might need to take in the array at hand
  //for the random grid- needs to generate random bacteria based on density the user provided
  static void generateBacteria(Cell *** array, int numCells, int columns, int rows);

  static void printGrid(Cell *** array, int rows, int columns);

  static void simulate(Cell *** array, int rows, int columns, string gameMode, string output, string fileName);


};
