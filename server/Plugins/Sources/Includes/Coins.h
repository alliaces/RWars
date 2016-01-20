#pragma once

#include "ABonus.h"
#include "APlayer.h"
#include "Map.h"

class Coins : public ABonus
{
 public:
  Coins();
  Coins(const Coins &);
  ~Coins();
  void collideBonus(AEntity *);  
  void tick(Map &map_);
 private:
  int timer_;
#ifdef __linux__
  static Coins *instance;
#endif
};
