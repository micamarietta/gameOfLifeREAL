#include "Game.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>


Game::Game(){
  //ctor
}

void Game::start(){
  string userInput;
  string modeInput;
  string mapFileName;
  string simulationPref;
  ifstream inFS;
  int numRows = 0;
  int numColumns = 0;
  double density = 0;
  string fileOutput = " ";



  cout << "Welcome to the Game of Life!" << endl;
  cout << "Would you like to upload a map file or play on a random map? (map or random)" << endl;
  cin >> userInput;


  //if they include a map file
  if(userInput == "map"){
    Cell *** gameGrid;
    char currentChar;
    string currentLine;
    int lineCount = 0;
    cout << "What is the name of the map file?" << endl;
    cin >> mapFileName;

    inFS.open(mapFileName);

    if(inFS.is_open()){
      cout << "Map file has been opened" << endl;
    }

    while(getline(inFS, currentLine)){
        if(lineCount == 0){
          //get numRows
          numRows = stoi(currentLine);
          cout << numRows << endl;
        }
        else if(lineCount == 1){
          // line 1 has the columns value
          //inFS >> numColumns;
          numColumns = stoi(currentLine);
          cout << numColumns << endl;

          //cout << "columns : " << numColumns << endl;

          //generate empty grid
          gameGrid = generateGrid(numRows, numColumns);

        }
        else{
          //read the grid and generate a grid of cells based upon it
          for(int j = 0; j < numColumns; ++j){
            gameGrid[lineCount - 2][j]->setCurIsAlive(currentLine[j] == 'X');
          }
        }
      lineCount++;
      //cout << lineCount << endl;
    }

    inFS.close();

    printGrid(gameGrid, numRows, numColumns);

    //ask what mode they want to play in
    cout << "What game mode would you like to play in? (classic, mirror, or donut)" << endl;
    cin >> modeInput;
    if(modeInput == "classic"){
      gameMode = "Classic";
    }
    else if(modeInput == "mirror"){
      gameMode = "Mirror";
    }
    else if(modeInput == "donut"){
      gameMode = "Donut";
    }else{
      cout << "That is not a valid game mode. Try again." << endl;
    }

    //get user preference on output of simulation
    cout << "How would you like your generations outputted (Pause between simulations, enter activates next generation, or output to a file)? (pause, enter, file)" << endl;
    cin >> simulationPref;
    if(simulationPref == "pause"){
      cout << "Brief pauses will occur between generations" << endl;
      simulate(gameGrid, numRows, numColumns, gameMode, simulationPref, fileOutput);
    }
    else if(simulationPref == "enter"){
      cout << "Press enter to activate the next generation" << endl;
      simulate(gameGrid, numRows, numColumns, gameMode, simulationPref, fileOutput);
    }
    else if(simulationPref == "file"){
      cout << "What is the file you want to output the generations to?" << endl;
      cin >> fileOutput;

      simulate(gameGrid, numRows, numColumns, gameMode, simulationPref, fileOutput);
    }
  }

  //if they are using a random simulation
  else if(userInput == "random"){
    cout << "Great!" << endl;

    //creating the dimensions
    cout << "It is time to create the dimensions of your game board!" << endl;

    //row input
    cout << "How many rows do you want in the grid?" << endl;
    cin >> numRows;

    //column input
    cout << "How many columns do you want in the grid?" << endl;
    cin >> numColumns;

    //create our game board
    Cell *** gameGrid = generateGrid(numRows, numColumns);

    //generating the random assignments of bacteria in the grid
    cout << "Enter a number between 0 and 1 to determine the initial population density of the world." << endl;
    cin >> density;

    //calculate the number of cells that will be populated
    int numOfCellsToPop = numRows * numColumns * density;


    generateBacteria(gameGrid, numOfCellsToPop,numColumns,numRows);
    printGrid(gameGrid, numRows, numColumns);

    //ask what mode they want to play in
    cout << "What game mode would you like to play in? (classic, mirror, or donut)" << endl;
    cin >> modeInput;
    if(modeInput == "classic"){
      gameMode = "Classic";
    }
    else if(modeInput == "mirror"){
      gameMode = "Mirror";
    }
    else if(modeInput == "donut"){
      gameMode = "Donut";
    }else{
      cout << "That is not a valid game mode. Try again." << endl;
    }

    //get user preference on output of simulation
    cout << "How would you like your generations outputted (Pause between simulations, enter activates next generation, or output to a file)? (pause, enter, file)" << endl;
    cin >> simulationPref;
    if(simulationPref == "pause"){
      cout << "Brief pauses will occur between generations" << endl;
      simulate(gameGrid, numRows, numColumns, gameMode, simulationPref, fileOutput);
    }
    else if(simulationPref == "enter"){
      cout << "Press enter to activate the next generation" << endl;
      simulate(gameGrid, numRows, numColumns, gameMode, simulationPref, fileOutput);
    }
    else if(simulationPref == "file"){
      cout << "What is the file you want to output the generations to?" << endl;
      cin >> fileOutput;
      simulate(gameGrid, numRows, numColumns, gameMode, simulationPref, fileOutput);
    }

//if their input is invalid
    else{
      cout << "Don't know what that means" << endl;
    }
  }
}

//returns the grid that was created
Cell *** Game::generateGrid(int row, int column){
  Cell *** myGrid = new Cell**[row];

  //create double pointer array
  for(unsigned int i = 0;i < row; ++i){
    myGrid[i] = new Cell*[column];
  }

  //loop through array and fill with values
  for (int i = 0; i < row; ++i){
    for(int j = 0; j < column; ++j){
      myGrid[i][j] = new Cell(i, j);
    }
  }

  return myGrid;
}

//randomly creates bacteria throughout the grid based on density
void Game::generateBacteria(Cell *** array, int numCells, int columns, int rows){
  cout << "generating bacteria.." << endl;
  srand(time(0));
  for(int i = 0; i < numCells; ++i){
    bool loop = true;
    while(loop){
      int randRow = rand() % rows;
      int randCol = rand() % columns;
      //cout << randRow << " rows and " << columns << " columns" << endl;
      Cell* curCell = array[randRow][randCol];
      if(!curCell->getCurIsAlive()){
        curCell->setCurIsAlive(true);
        loop = false;
      }
    }
  }
}


//cout statements to print the grid
void Game::printGrid(Cell *** array, int rows, int columns){

  for (unsigned int i = 0; i < rows; ++i){
    for(unsigned int j = 0; j < columns; ++j){
      cout << array[i][j]->cellToString();
    }
    cout << endl;
  }
}

//creates simulations for each generation
void Game::simulate(Cell *** array, int rows, int columns, string gameMode, string output, string fileName){
  bool gameOver = false;
  int simulationCount = 0;

  //while the game isnt over
  while(!gameOver){
    simulationCount++;

    //call all cell ToD functions to set the next IsAlive values
    //don't apply changes for this generation yet
    string curState = "";
    for( int i = 0; i < rows; ++i){
      for( int j = 0; j < columns; ++j){
        array[i][j]->thriveOrDie(gameMode, array, rows, columns);
        if (array[i][j]->getCurIsAlive()){
          curState = curState + "X";
        } else {
          curState = curState + "-";
        }
      }
    }

    //apply the changes
    string nextState = "";
    for(int i = 0; i < rows; ++i){
      for( int j = 0; j < columns; ++j){
        array[i][j]->applyChanges();
        if (array[i][j]->getCurIsAlive()){
          nextState = nextState + "X";
        } else {
          nextState = nextState + "-";
        }
      }
    }

    if(output == "pause"){
      usleep(100);
      cout << "Simulation " << simulationCount << endl;
      printGrid(array, rows, columns);
    }
    else if(output == "enter"){
      if(cin.get() == '\n'){
        cout << "Simulation " << simulationCount << endl;
        printGrid(array, rows, columns);
      }
    }else if(output == "file"){
      ofstream ofFS;
      ofFS.open(fileName, ios::app);

      ofFS << "Simulation " << simulationCount << endl;
      for (unsigned int i = 0; i < rows; ++i){
        for(unsigned int j = 0; j < columns; ++j){
          ofFS << array[i][j]->cellToString();
        }
        ofFS << endl;
      }

      ofFS.close();
    }

    //lose logic (no alive cells found)
    int aliveCount = 0;
    for(int i = 0; i < rows; ++i){
      for( int j = 0; j < columns; ++j){
        if(array[i][j]->getCurIsAlive()){
          ++aliveCount;
        }
      }
    }

    if(aliveCount == 0){
      if(output == "file"){
        gameOver = true;
        cout << "Everyone died" << endl;
        cout << "Hit enter to exit the program." << endl;
        if(cin.get() == '\n'){
          cout << "Program has ended" << endl;
        }
    }

    // win logic (grid state has not changed)
    if (curState == nextState){
      gameOver = true;
      cout << "You are stable!" << endl;
      cout << "Hit enter to exit the program." << endl;
      if(cin.get() == '\n'){
        cout << "Program has ended" << endl;
      }
    }
  }
}
}
