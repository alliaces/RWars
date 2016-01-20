#ifndef		_UTRHEAD_HPP_
#define		_UTRHEAD_HPP_

#include	<pthread.h>
#include	"IThread.h"

class UThread : public IThread
{
public:
  UThread(void *(*p_func)(void *), void *p_data);
  ~UThread();
  int		startThread();
  int		stopThread();
  int		waitThread();
  void		setFunc(void *(*)(void *));
  void		setData(void *);
  int		getExitCode();
private:
  void		*(*_func)(void *);
  void		*_data;
  pthread_t	_thread;
  int		_exitCode;
};

#endif
