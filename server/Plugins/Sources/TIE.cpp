#include "TIE.h"

#ifdef __linux__
TIE	*TIE::instance;
#endif

TIE::TIE() : AMonster(10, 5, 50, 50, "TIE")
{
  this->addSprite(7);
  this->idGlobal_ = 6;
  this->shotEntity_ = 4;
  this->spawnRate_ = 100;
}

TIE::TIE(const TIE &tie) : AMonster(tie)
{}

TIE::~TIE()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new TIE());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new TIE());
	}
}
#endif
