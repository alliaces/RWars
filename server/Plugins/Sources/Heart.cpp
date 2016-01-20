#include "Heart.h"

#ifdef __linux__
Heart	*Heart::instance;
#endif

Heart::Heart() : ABonus(20, 20)
{
  this->addSprite(90);
  this->idGlobal_ = 12;
}

Heart::Heart(const Heart &tie) : ABonus(tie)
{}

Heart::~Heart()
{}

void Heart::collideBonus(AEntity *playerEntity)
{
  APlayer* player = (APlayer*)playerEntity;
  player->heal(5);
}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Heart());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Heart());
	}
}
#endif
