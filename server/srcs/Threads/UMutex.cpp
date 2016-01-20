#include	"UMutex.h"

UMutex::UMutex()
{
	this->_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

UMutex::~UMutex()
{
	
}

void		UMutex::lockMutex()
{
	pthread_mutex_lock(&this->_mutex);
}

void		UMutex::unlockMutex()
{
	pthread_mutex_unlock(&this->_mutex);
}
