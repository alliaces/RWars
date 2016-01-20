#include "TIE3.h"

#ifdef __linux__
TIE3	*TIE3::instance;
#endif

TIE3::TIE3() : AMonster(10, 5, 50, 50, "TIE3")
{
  this->addSprite(7);
  this->idGlobal_ = 14;
  this->shotEntity_ = 4;
  this->spawnRate_ = 30;
  isFirst = true;
}

void TIE3::tick(Map &map_)
{
  if (isFirst)
    {
      AEntity *ent = (AEntity*)map_.createEntity(13);
      if (ent)
	ent->setPos(Vector2(this->getPosX() - 37, this->getPosY() - 37));
      ent = (AEntity*)map_.createEntity(13);
      if (ent)      
	ent->setPos(Vector2(this->getPosX(), this->getPosY() - 55));      
      ent = (AEntity*)map_.createEntity(13);
      if (ent)
	ent->setPos(Vector2(this->getPosX() + 52, this->getPosY() - 37));
      ent = (AEntity*)map_.createEntity(13);
      if (ent)
	ent->setPos(Vector2(this->getPosX() + 85, this->getPosY()));
      ent = (AEntity*)map_.createEntity(13);
      if (ent)
	ent->setPos(Vector2(this->getPosX() + 52, this->getPosY() + 52));
      ent = (AEntity*)map_.createEntity(13);
      if (ent)
	ent->setPos(Vector2(this->getPosX(), this->getPosY() + 85));
      ent = (AEntity*)map_.createEntity(13);
      if (ent)      
	ent->setPos(Vector2(this->getPosX() - 37, this->getPosY() + 52));
      isFirst = false;
    }
  if (this->shoot_ > 0)
    --this->shoot_;
  this->move(-1, 0);
}

TIE3::TIE3(const TIE3 &tie) : AMonster(tie)
{}

TIE3::~TIE3()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new TIE3());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new TIE3());
	}
}
#endif
