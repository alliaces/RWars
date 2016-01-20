#pragma once

#include <iostream>
#include "AMonster.h"
#include "Map.h"

class TIE3 : public AMonster
{
 public:
  TIE3();
  TIE3(const TIE3 &);
  ~TIE3();
  void tick(Map &map);
 private:
  bool isFirst;
#ifdef __linux__
  static TIE3 *instance;
#endif
};
