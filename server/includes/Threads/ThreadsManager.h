#pragma once
#ifndef	_WIN32
	#include	"UThread.hpp"
	#include	"UMutex.h"
#else
	#include	"WThread.h"
	#include	"WMutex.h"
#endif
#include	<vector>

struct thread_data_container
{
	void *data;
	void *(*function)(void *);
	std::vector<IThread*>	*threads;
	IThread					*me;
	IMutex					*locker;
};

class ThreadsManager
{
public:
	
	ThreadsManager();
	~ThreadsManager();
	void			newThread(void *(*p_func)(void *), void *p_data);
#ifndef	_WIN32
	static void		*launcher(void *);
#else
	static void		launcher(void *);
#endif
private:
	std::vector<IThread*>	_threads;
	IMutex					*_vectorMutex;
};
