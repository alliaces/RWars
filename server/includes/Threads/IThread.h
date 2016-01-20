#pragma once
class IThread
{
public:
	virtual int		startThread() = 0;
	virtual int		stopThread() = 0;
	virtual int		waitThread() = 0;
#ifndef	_WIN32
	virtual void	setFunc(void *(*)(void *)) = 0;
#else
	virtual void	setFunc(void (*)(void *)) = 0;
#endif
	virtual void	setData(void *) = 0;
};

