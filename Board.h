#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <queue>
#include <Player.h>

using namespace std;

struct card_t{
   string name;
   int property_index;
 };

class Board{

public:

  Board(int numPlayers,int numTurns);

  void playOneTurn(int numPlayers,int round);

  void prepareTurn(Player& player);

  void takeNormalTurn(Player& player, int turns);

  void takeJailTurn(Player& player);

  void changePlayerLocationOnRoll(Player& player,int location,int roll1,int roll2);

  void changePlayerLocationOther(Player& player, int& flag);

  void newPlayerLocation(Player& player,int location);

  void checkProperty(Player& player);

  void createCommunityCards();

  void createChanceCards();

  void takeTurn();

  int dieRoll();

  bool checkDoubles(int a, int b);

  void getChanceCard(Player& player);

  void getCommunityCard(Player& player);

  void goToJail(Player& player);

  void printFinalData();

  void makeVerbose();

  void setSeed(int num);

  void playGame();



private:

  int seedValue;

  int currentPlayer;

  int numTurns;

  int numberPlayers;

  bool verbose;

  vector<Player> playerVector;

  queue<card_t> communityChest;

  queue<card_t> chanceCards;

  vector<string> property_names;

  vector<int> propertyCounts;

  int defined_time;

  friend class BoardTest;


};

#endif
