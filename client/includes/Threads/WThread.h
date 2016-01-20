#pragma once
#include	<Windows.h>
#include	"IThread.h"

class WThread : public IThread
{
public:
	WThread(void (*p_func)(void *), void *p_data);
	~WThread();
	int		startThread();
	int		stopThread();
	int		waitThread();
	void	setFunc(void (*p_func)(void *));
	void	setData(void *);
	int		getExitCode();
private:
	void					(*_func)(void *);
	void					*_data;
	HANDLE					_thread;
	DWORD					_exitCode;
};