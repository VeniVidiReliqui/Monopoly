#ifndef PLAY_TEST_H
#define PLAY_TEST_H

#include "Player.h"

#include <iostream>
#include <cxxtest/TestSuite.h>

using namespace std;

class PlayerTest : public CxxTest::TestSuite {
public:

  void testGetJailCards(){
    Player p;
    p.getJailCardChance();
    p.getJailCardChest();
    TS_ASSERT(p.jailCardChance);
    TS_ASSERT(p.jailCardChest);
  }

  void testUseJailCards(){
    Player p;
    p.getJailCardChance();
    p.getJailCardChest();
    TS_ASSERT(p.jailCardChance);
    TS_ASSERT(p.jailCardChest);
    p.useJailCardChance();
    p.useJailCardChest();
    TS_ASSERT(! p.jailCardChance);
    TS_ASSERT(! p.jailCardChest);
  }

  void testGoJail(){
    Player p;
    p.goJail();
    TS_ASSERT_EQUALS(2, p.getJailTurns());
    TS_ASSERT_EQUALS(1, p.getJailedTimes());
  }

  void testOutOfJail(){
    Player p;
    p.goJail();
    TS_ASSERT_EQUALS(2, p.getJailTurns());
    TS_ASSERT_EQUALS(1, p.getJailedTimes());
    p.outOfJail();
    TS_ASSERT_EQUALS(0, p.getJailTurns());
    TS_ASSERT_EQUALS(1, p.getJailedTimes());
    p.goJail();
    TS_ASSERT_EQUALS(2, p.getJailTurns());
    TS_ASSERT_EQUALS(2, p.getJailedTimes());
    p.outOfJail();
    TS_ASSERT_EQUALS(0, p.getJailTurns());
    TS_ASSERT_EQUALS(2, p.getJailedTimes());
  }

  void testDecrementJailTurns(){
    Player p;
    p.goJail();
    TS_ASSERT_EQUALS(2, p.getJailTurns());
    TS_ASSERT_EQUALS(1, p.getJailedTimes());
    p.decrementJailTurns();
    TS_ASSERT_EQUALS(1,p.getJailTurns());
    p.decrementJailTurns();
    TS_ASSERT_EQUALS(0,p.getJailTurns());
  }

  void testGetJailTurns(){
    Player p;
    p.goJail();
    TS_ASSERT_EQUALS(2, p.getJailTurns());
    TS_ASSERT_EQUALS(1, p.getJailedTimes());
    p.outOfJail();
    TS_ASSERT_EQUALS(0, p.getJailTurns());
    TS_ASSERT_EQUALS(1, p.getJailedTimes());
    p.goJail();
    TS_ASSERT_EQUALS(2, p.getJailTurns());
    TS_ASSERT_EQUALS(2, p.getJailedTimes());
    p.outOfJail();
    TS_ASSERT_EQUALS(0, p.getJailTurns());
    TS_ASSERT_EQUALS(2, p.getJailedTimes());
  }

  void testChangeRoll(){
    Player p;
    p.rollOne(4);
    p.rollTwo(5);
    TS_ASSERT_EQUALS(4,p.getRollOne());
    TS_ASSERT_EQUALS(5,p.getRollTwo());
    p.rollOne(3);
    p.rollTwo(2);
    TS_ASSERT_EQUALS(3,p.getRollOne());
    TS_ASSERT_EQUALS(2,p.getRollTwo());
  }

  void testGetRoll(){
    Player p;
    p.rollOne(4);
    p.rollTwo(5);
    TS_ASSERT_EQUALS(4,p.getRollOne());
    TS_ASSERT_EQUALS(5,p.getRollTwo());
    p.rollOne(3);
    p.rollTwo(2);
    TS_ASSERT_EQUALS(3,p.getRollOne());
    TS_ASSERT_EQUALS(2,p.getRollTwo());
  }

  void testSetLocation(){
    Player p;
    p.setLocation(4);
    TS_ASSERT_EQUALS(4,p.getLocation());
    p.setLocation(8);
    TS_ASSERT_EQUALS(8,p.getLocation());
  }

  void testGetLocation(){
    Player p;
    p.setLocation(4);
    TS_ASSERT_EQUALS(4,p.getLocation());
    p.setLocation(8);
    TS_ASSERT_EQUALS(8,p.getLocation());
  }
};
#endif
