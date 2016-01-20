#include "Explosion.h"

#ifdef __linux__
Explosion	*Explosion::instance;
#endif

Explosion::Explosion() : AExplosion(0, 40, 40)
{
	int i = 12;
	while (i < 86)
	{
		this->addSprite(i);
		++i;
	}
	this->setTimer();
	this->idGlobal_ = 0;
}

Explosion::Explosion(const Explosion &other) : AExplosion(other)
{}

Explosion::~Explosion()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Explosion());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Explosion());
	}
}
#endif
