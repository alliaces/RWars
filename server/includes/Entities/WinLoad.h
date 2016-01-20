#pragma once

#include <exception>
#include <windows.h>

template <class T>
class WLoad
{
public:
	WLoad()
	{
		isClose = false;
	}
	~WLoad()
	{
		close();
	}

	T	*load(LPCSTR path)
	{
		open(path);
		return (creator());
	}

	HINSTANCE	open(LPCSTR path)
	{
		if ((this->inst = LoadLibrary(path)) == NULL)
			throw std::runtime_error("LoadLibrary");
		return (this->inst);
	}

	T	*creator()
	{
		if ((this->create = (T *(*)())GetProcAddress(this->inst, "create_instance")) == NULL)
			throw std::runtime_error("GetProcAddress");
		this->objet = this->create();
		return (this->objet);
	}

	void	close()
	{
		if (isClose)
		  return;
		isClose = true;
		FreeLibrary(this->inst);
	}
	
	T	*getObjet()
	{
		return (this->objet);
	}

private:
	BOOL isClose;
	T *(*create)();
	T *objet;
	HINSTANCE inst;
};
