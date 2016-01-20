#pragma once

#include <iostream>
#include "AMonster.h"
#include "Map.h"
#include "APlayer.h"

class TIE2 : public AMonster
{
 public:
  TIE2();
  TIE2(const TIE2 &);
  ~TIE2();
  void tick(Map &map);
 private:
#ifdef __linux__
  static TIE2 *instance;
#endif
};
