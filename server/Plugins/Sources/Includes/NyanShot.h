#pragma once

#include "AShot.h"

class NyanShot : public AShot
{
 public:
  NyanShot();
  NyanShot(const NyanShot &);
  ~NyanShot();

 private:
#ifdef __linux__
  static NyanShot *instance;
#endif
};
