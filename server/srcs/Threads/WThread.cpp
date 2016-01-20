#include <stdio.h>
#include "WThread.h"

WThread::WThread(void (*p_func)(void *), void *p_data)
{
	this->_func = p_func;
	this->_data = p_data;
}

WThread::~WThread()
{
}

int WThread::startThread()
{
	this->_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_func, _data, 0, NULL);
	if (this->_thread == NULL)
		return (-1);
	return (0);
}

int WThread::stopThread()
{
	GetExitCodeThread(this->_thread, &this->_exitCode);
	if (TerminateThread(this->_thread, this->_exitCode) == 0)
		return (-1);	
	return (0);
}

int WThread::waitThread()
{
	if (WaitForSingleObject(this->_thread, INFINITE) == WAIT_FAILED)
		return (-1);
	return (0);
}

void WThread::setFunc(void (*p_func)(void *))
{
	this->_func = p_func;
}

void WThread::setData(void *p_data)
{
	this->_data = p_data;
}

int WThread::getExitCode()
{
	return (this->_exitCode);
}
