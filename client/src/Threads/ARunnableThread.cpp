#include	"ARunnableThread.h"

#include <iostream>
ARunnableThread::ARunnableThread()
{
#ifndef _WIN32
  this->_thread = new UThread(&ARunnableThread::runner, this);
#else
  this->_thread = new WThread(&ARunnableThread::runner, this);
#endif
}

ARunnableThread::~ARunnableThread()
{
	
}

void		ARunnableThread::start()
{
  this->_thread->startThread();
}

void		ARunnableThread::stop()
{
	this->_thread->stopThread();
}

void		ARunnableThread::wait()
{
	this->_thread->waitThread();
}

#ifndef _WIN32
void		*ARunnableThread::runner(void *data)
{
  ARunnableThread	*plop;

  plop = (ARunnableThread *)data;
  return (plop->run(NULL));
}
#else
void		ARunnableThread::runner(void *data)
{
  ARunnableThread	*plop;

  plop = (ARunnableThread *)data;
  plop->run(NULL);
}
#endif
