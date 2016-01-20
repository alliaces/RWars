#pragma once

#include "ABonus.h"
#include "APlayer.h"

class Heart : public ABonus
{
 public:
  Heart();
  Heart(const Heart &);
  ~Heart();
  void collideBonus(AEntity *);  
 private:
#ifdef __linux__
  static Heart *instance;
#endif
};
