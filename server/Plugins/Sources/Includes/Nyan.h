#pragma once

#include "AMonster.h"

class Nyan : public AMonster
{
 public:
  Nyan();
  Nyan(const Nyan &);
  ~Nyan();

 private:
#ifdef __linux__
  static Nyan *instance;
#endif
};
