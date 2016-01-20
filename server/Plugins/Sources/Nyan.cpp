#include "Nyan.h"

#ifdef __linux__
Nyan	*Nyan::instance;
#endif

Nyan::Nyan() : AMonster(50, 5, 50, 26, "Nyan")
{
  this->addSprite(87);
  this->idGlobal_ = 9;
  this->shotEntity_ = 5;
  this->spawnRate_ = 5;
}

Nyan::Nyan(const Nyan &tie) : AMonster(tie)
{}

Nyan::~Nyan()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Nyan());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Nyan());
	}
}
#endif
