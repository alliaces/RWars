#pragma once

#include "AMonster.h"
#include "Map.h"
#include "AShot.h"

class Harrow : public AMonster
{
 public:
  Harrow();
  Harrow(const Harrow &);
  ~Harrow();
  void tick(Map &map);
 private:
  int timer_;
  int timer2_;
#ifdef __linux__
  static Harrow *instance;
#endif
};
