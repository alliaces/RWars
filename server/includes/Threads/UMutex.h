#ifndef				_UMUTEX_H_
#define				_UMUTEX_H_

#include			"IMutex.h"
#include			<pthread.h>

class UMutex : public IMutex
{
public:
	UMutex();
	~UMutex();
	void			lockMutex();
	void			unlockMutex();
private:
	pthread_mutex_t	_mutex;
};

#endif