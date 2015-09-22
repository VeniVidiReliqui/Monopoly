#ifndef CARDS_H
#define CARDS_H

using namespace std;

class Cards{
public:

  Cards();

  int getCardChance();

  int getCardCC();

  void replaceJailCardChance();

  void replaceJailCardCC();




private:

  struct card_t{
    string name;
    int id;
  };

};
#endif
