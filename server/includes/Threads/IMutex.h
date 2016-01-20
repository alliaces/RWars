#pragma once

class IMutex
{
public:
  virtual ~IMutex() {}
  virtual void	lockMutex() = 0;
  virtual void	unlockMutex() = 0;
};
