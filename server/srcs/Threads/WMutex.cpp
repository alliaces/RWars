#include	"WMutex.h"

WMutex::WMutex()
{
	InitializeCriticalSectionAndSpinCount(&this->_mutex, 0);
}

WMutex::~WMutex()
{
	DeleteCriticalSection(&this->_mutex);
}

void		WMutex::lockMutex()
{
	EnterCriticalSection(&this->_mutex);
}

void		WMutex::unlockMutex()
{
	LeaveCriticalSection(&this->_mutex);
}