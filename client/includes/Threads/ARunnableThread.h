#pragma once
#ifndef	_WIN32
#include	"UThread.hpp"
#else
#include	"WThread.h"
#endif

class ARunnableThread
{
 public:
  ARunnableThread();
  ~ARunnableThread();
  virtual void		*run(void *) = 0;
#ifndef	_WIN32
  static void		*runner(void *);
#else
  static void		runner(void *);
#endif
  void			start();
  void			stop();
  void			wait();
 private:
  IThread			*_thread;
};
