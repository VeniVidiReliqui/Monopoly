#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

class Player{
public:

  Player();

  void getJailCardChance();

  void getJailCardChest();

  void useJailCardChance();

  void useJailCardChest();

  int getJailedTimes();

  void goJail();

  void decrementJailTurns();

  int getJailTurns();

  void outOfJail();

  void rollOne(int num);

  void rollTwo(int num);

  int getRollOne();

  int getRollTwo();

  int getLocation();

  void setLocation(int value);

  int jailedTally;
  int jailTurnTally;
  bool jailCardChance;
  bool jailCardChest;

private:
  int location;

  int currentrollOne;
  int currentrollTwo;

};

#endif
