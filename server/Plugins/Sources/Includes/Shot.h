#pragma once

#include "AShot.h"

class Shot : public AShot
{
 public:
  Shot();
  Shot(const Shot &);
  ~Shot();

 private:
#ifdef __linux__
  static Shot *instance;
#endif
};
