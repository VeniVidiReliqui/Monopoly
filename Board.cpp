#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <time.h>

#include "Board.h"

using namespace std;

Board::Board(int numPlayers,int num){
  numTurns = num;
  numberPlayers = numPlayers;
  verbose = false;
//  if (seedValue) {
//    srand(seedValue);
//  }
//  else{
//    srand(time(NULL));
//  }
//
//  if (ver){
//    this->verbose = true;
//  }
//  else{
//    this->verbose = false;
//  }

  for (int i = 0; i < numPlayers; i++){
    Player player;
    playerVector.push_back(player);
  }
  srand(time(NULL));
  createCommunityCards();
  createChanceCards();

  property_names.push_back("Go");
  property_names.push_back("Mediterranean Avenue");
  property_names.push_back("Community Chest");
  property_names.push_back("Baltic Avenue");
  property_names.push_back("Income Tax");
  property_names.push_back("Reading Railroad");
  property_names.push_back("Oriental Avenue");
  property_names.push_back("Chance");
  property_names.push_back("Vermont Avenue");
  property_names.push_back("Connecticut Avenue");
  property_names.push_back("In Jail/Just Visiting");
  property_names.push_back("St. Charles Place");
  property_names.push_back("Electric Company");
  property_names.push_back("States Avenue");
  property_names.push_back("Virginia Avenue");
  property_names.push_back("Pennsylvania Railroad");
  property_names.push_back("St. James Place");
  property_names.push_back("Community Chest");
  property_names.push_back("Tennessee Avenue");
  property_names.push_back("New York Avenue");
  property_names.push_back("Free Parking");
  property_names.push_back("Kentucky Avenue");
  property_names.push_back("Chance");
  property_names.push_back("Indiana Avenue");
  property_names.push_back("Illinois Avenue");
  property_names.push_back("B. & O. Railroad");
  property_names.push_back("Alantic Avenue");
  property_names.push_back("Ventnor Avenue");
  property_names.push_back("Water Works");
  property_names.push_back("Marvin Gardens");
  property_names.push_back("Go To Jail");
  property_names.push_back("Pacific Avenue");
  property_names.push_back("North Carolina AVenue");
  property_names.push_back("Community Chest");
  property_names.push_back("Pennsylvania Avenue");
  property_names.push_back("Short Line");
  property_names.push_back("Chance");
  property_names.push_back("Park Place");
  property_names.push_back("Luxury Tax");
  property_names.push_back("Boardwalk");

  for (int y = 0; y < 40; y++){
    propertyCounts.push_back(0);
  }
}

void Board::playGame(){
  if (verbose == true){
  cout << "Num Players: " << numberPlayers << " Turns: " << numTurns << endl;
  cout << "Verbose: " << verbose << endl;
  }
  for (int i = 0; i < numTurns; i++){
    this->playOneTurn(numberPlayers,i+1);
  }
}

void Board::setSeed(int num){
  seedValue = num;
  srand(num);
}

void Board::playOneTurn(int numPlayers,int round){
  if (verbose==true){
    cout << "++++++++++++++++++++"<< endl;
    cout << "Starting round " << round << endl;
  }

  for (int i = 0; i < numPlayers; i++){

    if (verbose==true){
      cout << "Player " << i << " starting on " << property_names[playerVector[i].getLocation()] << endl;
      currentPlayer = i;
    }

    this->prepareTurn(playerVector[i]);

  }
}

void Board::prepareTurn(Player& player){

  if (player.jailTurnTally > 0){
    takeJailTurn(player);
  }
  else{
    takeNormalTurn(player,0);
  }
}

void Board::takeJailTurn(Player& player){
  if (player.jailCardChance == true){
    player.useJailCardChance();
    player.outOfJail();

    if (verbose==true){
      cout << "Player " << currentPlayer << " used a get out of jail free card" << endl;
    }

    card_t outJ;
    outJ.name = "Get Out of Jail Free";
    outJ.property_index = -1;
    this->chanceCards.push(outJ);

    takeNormalTurn(player, 0);

    return;
  }
  if (player.jailCardChest == true){
    player.useJailCardChest();
    player.outOfJail();

    if (verbose==true){
      cout << "Player " << currentPlayer << " used a get out of jail free card" << endl;
    }

    card_t five;
    five.name = "Get Out of Jail Free";
    five.property_index = -1;
    this->communityChest.push(five);

    takeNormalTurn(player, 0);

    return;
  }

  player.rollOne(this->dieRoll());
  player.rollTwo(this->dieRoll());

  if (verbose==true){
    cout << "Player " << currentPlayer << " rolled " << player.getRollOne() << "+" << player.getRollTwo() << endl;
  }

  if (checkDoubles(player.getRollOne(),player.getRollTwo())){
    player.outOfJail();
    changePlayerLocationOnRoll(player,player.getLocation(),player.getRollOne(),player.getRollTwo());
    if(verbose){
      cout << "- doubles, releasing from jail." << endl;
      cout << "Player " << currentPlayer << " landed on " << property_names[playerVector[currentPlayer].getLocation()] << endl;

    }
    this->takeNormalTurn(player, 1);
    return;
  }
  if (player.getJailTurns() == 0){
    if (verbose==true){
      cout << " - Third roll from jail, releasing." << endl;
      player.outOfJail();
      changePlayerLocationOnRoll(player,player.getLocation(),player.getRollOne(),player.getRollTwo());
      return;
    }
  }
  player.decrementJailTurns();
  if (verbose==true){
    cout << " - still in jail" << endl;
  }
  return;
}

void Board::goToJail(Player& player){
  this->newPlayerLocation(player,10);
  player.goJail();
}

void Board::takeNormalTurn(Player& player, int turns){
  int turnCount = turns;
  if (turnCount == 3){
    goToJail(player);
    turnCount = 0;
    if (verbose==true){
      cout << "Player " << currentPlayer << " rolled 3 doubles, go to jail." << endl;
    }
    return;
  }

  player.rollOne(this->dieRoll());
  player.rollTwo(this->dieRoll());
  turnCount++;

  if (verbose==true){
    cout << "Player " << currentPlayer << " rolls " << player.getRollOne() << "+" << player.getRollTwo() << endl;
  }
  if (turnCount == 3){
    if (this->checkDoubles(player.getRollOne(),player.getRollTwo())){
      goToJail(player);
      if (verbose==true){
        cout << "Player " << currentPlayer << " rolled 3 doubles, go to jail." << endl;
      }
      return;
    }
  }

  this->changePlayerLocationOnRoll(player,player.getLocation(),player.getRollOne(),player.getRollTwo());

  if (verbose==true){
    cout << "Player " << currentPlayer << " landed on " << property_names[player.getLocation()] << endl;
  }

  this->checkProperty(player);

  if (this->checkDoubles(player.getRollOne(),player.getRollTwo())){
    takeNormalTurn(player, turnCount++);
  }


  return;
}

void Board::newPlayerLocation(Player& player,int location){
  player.setLocation(location);//sets new player location
  propertyCounts[location]++;//saves number of times players land on property
}

void Board::changePlayerLocationOnRoll(Player& player,int location, int rolla, int rollb){
  int newLocation = ((location + rolla + rollb)%40);
  newPlayerLocation(player,newLocation);
}

void Board::changePlayerLocationOther(Player& player, int& flag){
  if (flag >= 0){
    newPlayerLocation(player,flag);
  }

  if (flag < 0){
    switch (flag){

      case -2:
        //go Utility
        if ((player.getLocation() < 12) || (player.getLocation() > 28)){ //Shit...
          newPlayerLocation(player, 12);
        }
        else{
          newPlayerLocation(player,28);
        }
        if (verbose==true){
          cout << "Player " << currentPlayer << " landed on " << property_names[player.getLocation()] << endl;
        }
        return;

      case -3:
        //go back 3 spaces
        newPlayerLocation(player,player.getLocation() - 3);
        if (verbose==true){
          cout << "Player " << currentPlayer << " landed on " << property_names[player.getLocation()] << endl;
        }
        return;

      case -4:
        //go nearest RR
        if (player.getLocation() == 7){
          newPlayerLocation(player,15);
        }
        else if (player.getLocation() == 22){ //THIS FUCKING PIECE OF SHIT
          newPlayerLocation(player,25);
        }
        else{
          newPlayerLocation(player,5);
        }
        if (verbose==true){
          //cout << "Player " << currentPlayer << " landed on " << property_names[player.getLocation()] << endl;
        }
        return;
    }
  }
}

void Board::checkProperty(Player& player){
  //check for Community Chest
  if ((player.getLocation() == 2) || (player.getLocation() == 17) || (player.getLocation() == 33)){
    this->getCommunityCard(player);
  }
  //check for Chance
  if ((player.getLocation() == 7) || (player.getLocation() == 22) || (player.getLocation() == 36)){
    this->getChanceCard(player);
  }
  //check for Go To Jail
  if (player.getLocation() == 30){
    this->goToJail(player);
  }
}

void Board::getCommunityCard(Player& player){
  if (verbose==true){
    cout << " -> Community Chest - ";
  }
  card_t card = communityChest.front();
  communityChest.pop();
  if (verbose==true){
    cout << card.name << endl;
  }
  //check for Jail Free Card
  if (card.property_index == -1){
    player.getJailCardChest();
    return;
  }
  //check for card that moves player
  if (card.property_index >= 0){
    changePlayerLocationOther(player, card.property_index);
  }
  //put card back if not Jail Free Card
  communityChest.push(card);
  return;
}

void Board::getChanceCard(Player& player){
  if (verbose==true){
    cout << " -> Chance - ";
  }
  card_t card = chanceCards.front();
  chanceCards.pop();
  if (verbose==true){
    cout << card.name << endl;
  }
  //check for Jail Free Card
  if (card.property_index == -1){
    player.getJailCardChance();
    return;
  }
  //check for Go To Jail Card
  if (card.property_index == 10){
    this->goToJail(player);
  }
  //check for card that moves player
  if (card.property_index >= 0){
    changePlayerLocationOther(player, card.property_index);
  }
  if (card.property_index < 0){
    changePlayerLocationOther(player, card.property_index);
  }
  //put card back if not Jail Free Card
  chanceCards.push(card);
  return;
}

void Board::createCommunityCards(){
  card_t one;
  one.name = "Advance to Go";
  one.property_index = 0;
  this->communityChest.push(one);
  card_t two;
  two.name = "Bank error in your favor";
  two.property_index = -9;
  this->communityChest.push(two);
  card_t three;
  three.name = "Doctor's fees";
  three.property_index = -9;
  this->communityChest.push(three);
  card_t four;
  four.name = "From sale of stock you get $50";
  four.property_index = -9;
  this->communityChest.push(four);
  card_t five;
  five.name = "Get Out of Jail Free";
  five.property_index = -1;
  this->communityChest.push(five);
  card_t six;
  six.name = "Go to Jail";
  six.property_index = 10;
  this->communityChest.push(six);
  card_t seven;
  seven.name = "Grand Opera opening";
  seven.property_index = -9;
  this->communityChest.push(seven);
  card_t eight;
  eight.name = "Xmas fund matures";
  eight.property_index = -9;
  this->communityChest.push(eight);
  card_t nine;
  nine.name = "Income tax refund";
  nine.property_index = -9;
  this->communityChest.push(nine);
  card_t ten;
  ten.name = "It is your birthday";
  ten.property_index = -9;
  this->communityChest.push(ten);
  card_t eleven;
  eleven.name = "Life insurance matures";
  eleven.property_index = -9;
  this->communityChest.push(eleven);
  card_t twelve;
  twelve.name = "Pay hospital fees of $100";
  twelve.property_index = -9;
  this->communityChest.push(twelve);
  card_t thirteen;
  thirteen.name = "Pay school fees of $150";
  thirteen.property_index = -9;
  this->communityChest.push(thirteen);
  card_t fourteen;
  fourteen.name = "Receive for Services $25";
  fourteen.property_index = -9;
  this->communityChest.push(fourteen);
  card_t fifteen;
  fifteen.name = "You are assessed for street repairs";
  fifteen.property_index = -9;
  this->communityChest.push(fifteen);
  card_t sixteen;
  sixteen.name = "You have won second prize in a beauty contest";
  sixteen.property_index = -9;
  this->communityChest.push(sixteen);
  card_t seventeen;
  seventeen.name = "You inherit $100";
  seventeen.property_index = -9;
  this->communityChest.push(seventeen);
}

void Board::createChanceCards(){
  card_t Go;
  Go.name = "Advance to Go";
  Go.property_index = 0;
  this->chanceCards.push(Go);
  card_t Illi;
  Illi.name = "Advance to Illinois Ave.";
  Illi.property_index = 24;
  this->chanceCards.push(Illi);
  card_t Chpl;
  Chpl.name = "Advance to St. Charles Place";
  Chpl.property_index = 11;
  this->chanceCards.push(Chpl);
  card_t Util;
  Util.name = "Advance token to nearest Utility";
  Util.property_index = -2;
  this->chanceCards.push(Util);
  card_t RR;
  RR.name = "Advance to nearest Railroad";
  RR.property_index = -4;
  this->chanceCards.push(RR);
  card_t bank;
  bank.name = "Bank pays you divident of $50";
  bank.property_index = -9;
  this->chanceCards.push(bank);
  card_t outJ;
  outJ.name = "Get Out of Jail Free";
  outJ.property_index = -1;
  this->chanceCards.push(outJ);
  card_t b3;
  b3.name = "Go back 3 spaces";
  b3.property_index = -3;
  this->chanceCards.push(b3);
  card_t goj;
  goj.name = "Go to Jail";
  goj.property_index = 10;
  this->chanceCards.push(goj);
  card_t rep;
  rep.name = "Make general repairs on all your property";
  rep.property_index = -9;
  this->chanceCards.push(rep);
  card_t poor;
  poor.name = "Pay poor tax of $15";
  poor.property_index = -9;
  this->chanceCards.push(poor);
  card_t Read;
  Read.name = "Take a ride on the Reading Railroad";
  Read.property_index = 5;
  this->chanceCards.push(Read);
  card_t Bdwk;
  Bdwk.name = "Advance token to Boardwalk";
  Bdwk.property_index = 39;
  this->chanceCards.push(Bdwk);
  card_t chmn;
  chmn.name = "You have been elected Charirman of the Board";
  chmn.property_index = -9;
  this->chanceCards.push(chmn);
  card_t loan;
  loan.name = "Your building and loan matures";
  loan.property_index = -9;
  this->chanceCards.push(loan);
  card_t cwd;
  cwd.name = "You have won a crossword competition";
  cwd.property_index = -9;
  this->chanceCards.push(cwd);
}

int Board::dieRoll(){
  return rand()%6+1;
}

bool Board::checkDoubles(int a, int b){
  if (a == b){
    return true;
  }
  else{
    return false;
  }
}

void Board::printFinalData(){
  cout << endl;
  for (int i = 0; i < 40; i++){
    cout << property_names[i] << " :: " << propertyCounts[i] << endl;
  }
}

void Board::makeVerbose(){
  this->verbose = true;
}


