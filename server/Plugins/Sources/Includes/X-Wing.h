#pragma once

#include "APlayer.h"

class XWing : public APlayer
{
 public:
  XWing();
  XWing(const XWing &);
  ~XWing();

 private:
  #ifdef __linux__
  static XWing *instance;
  #endif
};
