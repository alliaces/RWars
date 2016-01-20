#include "Coins.h"

#ifdef __linux__
Coins	*Coins::instance;
#endif

Coins::Coins() : ABonus(20, 20)
{
  this->addSprite(92);
  this->addSprite(93);
  this->addSprite(94);
  this->addSprite(95);
  this->addSprite(96);
  this->addSprite(97);
  this->idGlobal_ = 15;
  timer_ = 0;
}

Coins::Coins(const Coins &tie) : ABonus(tie)
{}

Coins::~Coins()
{}

void Coins::tick(Map &map_)
{
  if (timer_ > 10)
    {
      this->currentSprite_++;
      if (this->currentSprite_ > 5)
	this->currentSprite_ = 0;
      timer_ = 0;
    }
  timer_++;
  this->move(-1, 0);
}

void Coins::collideBonus(AEntity *playerEntity)
{
  APlayer* player = (APlayer*)playerEntity;
  player->addScore(100);
}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Coins());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Coins());
	}
}
#endif
