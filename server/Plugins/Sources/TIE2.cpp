#include "TIE2.h"

#ifdef __linux__
TIE2	*TIE2::instance;
#endif

TIE2::TIE2() : AMonster(10, 5, 90, 40, "TIE2")
{
  this->addSprite(86);
  this->idGlobal_ = 8;
  this->shotEntity_ = 4;
  this->spawnRate_ = 20;
  this->tickOverride_ = true;
}

void TIE2::tick(Map &map_)
{
  if (this->shoot_ > 0)
    --this->shoot_;
  AEntity* play = NULL;
  for (std::vector<AEntity *>::iterator it = map_.begin(); it != map_.end(); it++)
    {
      if ((*it)->getType() == "Player" && !((APlayer*)(*it))->isDead())
	{
	  if (play == NULL)
	    play = *it;
	  else if (play->getPosY() > (*it)->getPosY())
	    play = *it;
	}
    }
  if (play != NULL)
    { 
      if (play->getPosY() < this->getPosY())
	this->move(-1, -1);
      else if (play->getPosY() > this->getPosY())
	this->move(-1, 1);
      else
	this->move(-1, 0);
    }
  else
    this->move(-1, 0);
}

TIE2::TIE2(const TIE2 &tie) : AMonster(tie)
{}

TIE2::~TIE2()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new TIE2());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new TIE2());
	}
}
#endif
