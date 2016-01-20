#include "Shot.h"

#ifdef __linux__
Shot	*Shot::instance;
#endif

Shot::Shot() : AShot(5, 25, 7)
{
  this->addSprite(10);
  this->idGlobal_ = 4;
}

Shot::Shot(const Shot &shot) : AShot(shot)
{}

Shot::~Shot()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Shot());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Shot());
	}
}
#endif
