#include "AMonster.h"

AMonster::AMonster(int health, int dmg, int width, int height, const std::string &name) : AEntity(width, height)
{
  this->health_ = health;
  this->maxHealth_ = health;
  this->dmg_ = dmg;
  this->name_ = name;
  this->shoot_ = 300;
  this->type = "Monster";
  this->shotEntity_ = -1;
  this->spawnRate_ = 100;
}

AMonster::AMonster(const AMonster &other) : AEntity(other)
{
  this->health_ = other.health_;
  this->maxHealth_ = other.maxHealth_;
  this->dmg_ = other.dmg_;
  this->name_ = other.name_;
  this->shoot_ = other.shoot_;
  this->type = other.type;
  this->shotEntity_ = other.shotEntity_;
  this->spawnRate_ = other.spawnRate_;
}

AMonster &AMonster::operator=(const AMonster &other)
{
  if (&other != this)
  {
    this->id_ = other.id_;
    this->currentSprite_ = other.currentSprite_;
    this->health_ = other.health_;
    this->maxHealth_ = other.maxHealth_;
    this->dmg_ = other.dmg_;
    this->name_ = other.name_;
    this->pos_ = other.pos_;
    this->size_ = other.size_;
    this->sprites_ = other.sprites_;
    this->shoot_ = other.shoot_;
    this->type = other.type;
    this->shotEntity_ = other.shotEntity_;
    this->spawnRate_ = other.spawnRate_;
  }
  return *this;
}

AMonster::~AMonster()
{

}

int AMonster::getSpawnRate() const
{
  return this->spawnRate_;
}

int AMonster::getDmg() const
{
  return this->dmg_;
}

int AMonster::getHealth() const
{
  return this->health_;
}

int AMonster::getMaxHealth() const
{
  return this->maxHealth_;
}

int AMonster::getShoot() const
{
  return this->shoot_;
}

int AMonster::getShotEntity() const
{
  return this->shotEntity_;
}

void AMonster::refreshShoot()
{
  this->shoot_ = 300;
}

const std::string &AMonster::getName() const
{
  return this->name_;
}

void AMonster::takeDmg(int dmgTaken)
{
  if (dmgTaken > 0)
  {
    this->health_ -= dmgTaken;
    if (this->health_ < 0)
      this->health_ = 0;
  }
}

void AMonster::tick(Map &map)
{
  (void) map;
  if (this->shoot_ > 0)
    --this->shoot_;
  this->move(-1, 0);
}

const std::string &AMonster::getType() const
{
  return this->type;
}
