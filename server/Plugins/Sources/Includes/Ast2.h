#pragma once

#include "ABlock.h"

class Ast2 : public ABlock
{
 public:
  Ast2();
  Ast2(const Ast2 &);
  ~Ast2();

 private:
#ifdef __linux__
  static Ast2 *instance;
#endif
};
