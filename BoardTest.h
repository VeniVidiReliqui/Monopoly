#ifndef BOARD_TEST_H
#define BOARD_TEST_H

#include <Board.h>

#include <iostream>
#include <vector>
#include <string>
#include <cxxtest/TestSuite.h>

using namespace std;

class BoardTest : public CxxTest::TestSuite {
public:

  void testcheckVerbose(){
    Board b(2,1);
    TS_ASSERT(! b.verbose);
    b.makeVerbose();
    TS_ASSERT(b.verbose);
  }

  void testCheckDoubleTrue(){
    Board b(2,1);
    TS_ASSERT(! b.checkDoubles(1,2));
  }

  void testCheckDoubleFalse(){
    Board b(2,1);
    TS_ASSERT(! b.checkDoubles(1,2));
  }

  void testSetSeed(){
    Board b(2,1);
    b.setSeed(10);
    TS_ASSERT_EQUALS(10,b.seedValue);
  }

  void testConstructor(){
    Board b(2,1);
    TS_ASSERT_EQUALS(2,b.playerVector.size());
    TS_ASSERT_EQUALS(2,b.numberPlayers);
    TS_ASSERT_EQUALS(1,b.numTurns);
    TS_ASSERT_EQUALS(17,b.communityChest.size());
    TS_ASSERT_EQUALS(16,b.chanceCards.size());
    TS_ASSERT_EQUALS(40,b.property_names.size());
    TS_ASSERT(! b.verbose);
    TS_ASSERT_EQUALS(40,b.propertyCounts.size());
  }

  void testTakeNormalTurn(){
    Board b(2,1);
    b.playerVector[0].setLocation(1);
    b.playerVector[1].setLocation(1);
    TS_ASSERT_EQUALS(1,b.playerVector[0].getLocation());
    b.takeNormalTurn(b.playerVector[0],0);
    b.takeNormalTurn(b.playerVector[1],0);
    TS_ASSERT(1 != b.playerVector[0].getLocation());
    TS_ASSERT(1 != b.playerVector[1].getLocation());
  }

  void testPlayOneTurn(){
    Board b(2,1);
    b.playerVector[0].setLocation(1);
    b.playerVector[1].setLocation(1);
    TS_ASSERT_EQUALS(1,b.playerVector[0].getLocation());
    b.playOneTurn(2,1);
    TS_ASSERT(1 != b.playerVector[0].getLocation());
    TS_ASSERT(1 != b.playerVector[1].getLocation());
  }

  void testChangePlayerLocationOnRoll(){
    Board b(1,1);
    b.changePlayerLocationOnRoll(b.playerVector[0],0,3,3);
    TS_ASSERT(6 == b.playerVector[0].getLocation());
    TS_ASSERT(1 == b.propertyCounts[6]);
  }

  void testTakeJailTurn(){
    Board b(1,1);
    b.playerVector[0].getJailCardChance();
    b.playerVector[0].getJailCardChest();
    b.playerVector[0].setLocation(10);
    b.takeJailTurn(b.playerVector[0]);
    TS_ASSERT(! b.playerVector[0].jailCardChance);
    TS_ASSERT(10 != b.playerVector[0].getLocation());
    b.playerVector[0].setLocation(10);
    b.takeJailTurn(b.playerVector[0]);
    TS_ASSERT(! b.playerVector[0].jailCardChest);
    TS_ASSERT(10 != b.playerVector[0].getLocation());
    b.playerVector[0].setLocation(10);
    b.takeJailTurn(b.playerVector[0]);
    if (b.playerVector[0].getRollOne() == b.playerVector[0].getRollTwo()){
      TS_ASSERT( 10 != b.playerVector[0].getLocation());
    }
    else if(b.playerVector[0].getJailTurns() == 0){
      TS_ASSERT( 10 != b.playerVector[0].getLocation());
    }
    else{
      TS_ASSERT( 10 == b.playerVector[0].getLocation());
    }
  }

  void testGoToJail(){
    Board b(1,1);
    b.goToJail(b.playerVector[0]);
    TS_ASSERT_EQUALS(10, b.playerVector[0].getLocation());
  }

  void testNewPlayerLocation(){
    Board b(1,1);
    b.newPlayerLocation(b.playerVector[0],8);
    TS_ASSERT(8 == b.playerVector[0].getLocation());
    TS_ASSERT(1 == b.propertyCounts[8]);
  }

  void testChangePlayerLocationOther(){
    Board b(1,1);
    int value = 2;
    b.changePlayerLocationOther(b.playerVector[0],value);
    TS_ASSERT_EQUALS(2,b.playerVector[0].getLocation());
    value = -2;
    b.changePlayerLocationOther(b.playerVector[0],value);
    TS_ASSERT_EQUALS(28,b.playerVector[0].getLocation());
  }

  void testCheckProperty(){
    Board b(1,1);

    b.playerVector[0].setLocation(30);
    b.checkProperty(b.playerVector[0]);
    TS_ASSERT(0 != b.playerVector[0].jailedTally);
  }

  void testCreateCommunityChestCards(){
    Board b(1,1);
    TS_ASSERT_EQUALS(17,b.communityChest.size());
  }

  void testCreateChanceCards(){
    Board b(1,1);
    TS_ASSERT_EQUALS(16,b.chanceCards.size());
  }



};

#endif
