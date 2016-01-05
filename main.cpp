#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <Board.h>
#include <Player.h>

using namespace std;

//expects arguments: numPlayers numTurns
int main(int argc, char* argv[]){

  int numPlayers = atoi(argv[1]);
  int numTurns = atoi(argv[2]);

  Board t(numPlayers,numTurns);

  //seed rand
  if (argc >= 4){
    t.setSeed(atoi(argv[3]));
    if (argc >= 5){
      t.makeVerbose();
    }
  }

  //toggle verbose


  //play specified number of terms
  t.playGame();

  t.printFinalData();
  return 1;
}
