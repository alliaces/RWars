#pragma once

#include "ABlock.h"

class Ast : public ABlock
{
 public:
  Ast();
  Ast(const Ast &);
  ~Ast();

 private:
#ifdef __linux__
  static Ast *instance;
#endif
};
