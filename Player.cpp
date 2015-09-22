#include<iostream>
#include<string>
#include<list>
#include<vector>

#include"Player.h"

using namespace std;

Player::Player(){
  jailCardChance = false;
  jailCardChest = false;
  jailedTally = 0;
  jailTurnTally = 0;
  location = 0;
  currentrollOne = 0;
  currentrollTwo = 0;
}

void Player::rollOne(int num){
  this->currentrollOne = num;
}

int Player::getJailTurns(){
  return this->jailTurnTally;
}

void Player::rollTwo(int num){
  this->currentrollTwo = num;
}

int Player::getRollOne(){
  return this->currentrollOne;
}

int Player::getRollTwo(){
  return this->currentrollTwo;
}

void Player::getJailCardChance(){
  this->jailCardChance = true;
}

void Player::getJailCardChest(){
  this->jailCardChest = true;
}

void Player::useJailCardChance(){
  this->jailCardChance = false;
}

void Player::useJailCardChest(){
  this->jailCardChest = false;
}

void Player::goJail(){
  //increment number of times in jail
  this->jailedTally++;

  //set number of turns to be in jail
  this->jailTurnTally = 2;
}

void Player::decrementJailTurns(){
  this->jailTurnTally--;
}

void Player::outOfJail(){
  this->jailTurnTally = 0;
}

int Player::getLocation(){
  return this->location;
}

void Player::setLocation(int value){
  this->location = value;
}

int Player::getJailedTimes(){
  return this->jailedTally;
}
