#include "Harrow.h"

#ifdef __linux__
Harrow	*Harrow::instance;
#endif

Harrow::Harrow() : AMonster(1000, 5, 630, 179, "Harrow")
{
  this->addSprite(89);
  this->idGlobal_ = 10;
  this->shotEntity_ = 4;
  this->spawnRate_ = 5;
  this->timer_ = 0;
  this->timer2_ = 0;
}

void Harrow::tick(Map &map_)
{
  if (timer2_ > 100)
    {
      AEntity *ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY()));
	}      
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 10));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 20));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 30));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 40));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 50));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 60));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 70));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 80));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 90));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 100));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 110));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 120));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 130));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 140));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 150));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 160));
	}
      ent = (AEntity*)map_.createEntity(4);
      if (ent)
	{
	  ((AShot*)(ent))->shoot(this->getId(), 5, -1);
	  ent->setPos(Vector2(this->getPosX() - 26, this->getPosY() + 170));      
	}
      timer2_ = 0;
    }
  if (timer_ > 10)
    {
      timer2_++;
      timer_ = 0;
      this->move(-1,0);
    }
  timer_++;
}

Harrow::Harrow(const Harrow &tie) : AMonster(tie)
{}

Harrow::~Harrow()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Harrow());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Harrow());
	}
}
#endif
