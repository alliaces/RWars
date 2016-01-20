#include "NyanShot.h"

#ifdef __linux__
NyanShot	*NyanShot::instance;
#endif

NyanShot::NyanShot() : AShot(4, 30, 15)
{
  this->addSprite(88);
  this->idGlobal_ = 5;
}

NyanShot::NyanShot(const NyanShot &shot) : AShot(shot)
{}

NyanShot::~NyanShot()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new NyanShot());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new NyanShot());
	}
}
#endif
