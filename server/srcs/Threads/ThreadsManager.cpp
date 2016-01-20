#include "ThreadsManager.h"

ThreadsManager::ThreadsManager()
{
#ifndef	_WIN32
	this->_vectorMutex = new UMutex;
#else
	this->_vectorMutex = new WMutex;
#endif
}

ThreadsManager::~ThreadsManager()
{
	delete this->_vectorMutex;
}

void			ThreadsManager::newThread(void *(*p_func)(void *), void *p_data)
{
	struct thread_data_container	*bullshit = new struct thread_data_container;
	IThread							*newElem;

	bullshit->data = p_data;
	bullshit->function = p_func;
	bullshit->locker = this->_vectorMutex;
#ifndef	_WIN32
	newElem = new UThread(&ThreadsManager::launcher, (void *)bullshit);
#else
	newElem = new WThread(&ThreadsManager::launcher, (void *)bullshit);
#endif
	bullshit->threads = &this->_threads;
	bullshit->me = newElem;
	newElem->startThread();
	this->_threads.push_back(newElem);
}

#ifndef	_WIN32
void		*ThreadsManager::launcher(void *data)
{
	struct	thread_data_container				*nice_bullshit;
	void							*(*func)(void *);
	void							*tosend;
	IThread							*me;
	std::vector<IThread*>			*threads;
	std::size_t						i;
	IMutex							*locker;

	i = 0;
	nice_bullshit = (struct thread_data_container *)data;
	me = nice_bullshit->me;
	threads = nice_bullshit->threads;
	func = nice_bullshit->function;
	tosend = nice_bullshit->data;
	locker = nice_bullshit->locker;
	delete nice_bullshit;
	func(tosend);
	locker->lockMutex();
	while (i < threads->size() && me != threads->at(i))
		i++;
	if (i < threads->size())
		threads->erase(threads->begin() + i);
	locker->unlockMutex();
	return (NULL);
}
#else
void		ThreadsManager::launcher(void *data)
{
	struct	thread_data_container	*nice_bullshit;
	void							*(*func)(void *);
	void							*tosend;
	IThread							*me;
	std::vector<IThread*>			*threads;
	std::size_t						i;
	IMutex							*locker;

	i = 0;
	nice_bullshit = (struct thread_data_container *)data;
	me = nice_bullshit->me;
	threads = nice_bullshit->threads;
	func = nice_bullshit->function;
	tosend = nice_bullshit->data;
	locker = nice_bullshit->locker;
	delete nice_bullshit;
	func(tosend);
	locker->lockMutex();
	while (i < threads->size() && me != threads->at(i))
		i++;
	if (i < threads->size())
		threads->erase(threads->begin() + i);
	locker->unlockMutex();
}
#endif
