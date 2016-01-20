#pragma once

#include "AMonster.h"

class TIE : public AMonster
{
 public:
  TIE();
  TIE(const TIE &);
  ~TIE();

 private:
#ifdef __linux__
  static TIE *instance;
#endif
};
