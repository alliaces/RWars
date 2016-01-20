#include "UThread.hpp"

UThread::UThread(void *(*p_func)(void *), void *p_data)
{
  this->_func = p_func;
  this->_data = p_data;
}

UThread::~UThread()
{
}

int	UThread::startThread()
{
  if (pthread_create(&this->_thread, NULL, this->_func, this->_data) != 0)
    return (-1);
  return (0);
}

int	UThread::stopThread()
{
  return (pthread_cancel(this->_thread));
}

int	UThread::waitThread()
{
  return (pthread_join(this->_thread, (void**)&this->_exitCode));
}

void	UThread::setFunc(void *(*p_func)(void *))
{
  this->_func = p_func;
}

void	UThread::setData(void *p_data)
{
  this->_data = p_data;
}

int	UThread::getExitCode()
{
  return (this->_exitCode);
}
