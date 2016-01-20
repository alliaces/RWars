#pragma once

#include "AExplosion.h"

class Explosion : public AExplosion
{
 public:
  Explosion();
  Explosion(const Explosion &);
  ~Explosion();

 private:
#ifdef __linux__
  static Explosion *instance;
#endif
};
