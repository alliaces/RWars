#pragma once

#include				"IMutex.h"
#include				<windows.h>

class WMutex : public IMutex
{
public:
	WMutex();
	~WMutex();
	void				lockMutex();
	void				unlockMutex();
private:
	CRITICAL_SECTION	_mutex;
};