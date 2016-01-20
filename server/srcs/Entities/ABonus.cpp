#include "ABonus.h"

ABonus::ABonus(int width, int height) : AEntity(width, height)
{
  this->spawnRate_ = 100;
  this->type = "Bonus";
}

ABonus::ABonus(const ABonus &other) : AEntity(other)
{
  this->spawnRate_ = other.spawnRate_;
  this->type = other.type;
}

ABonus &ABonus::operator=(const ABonus &other)
{
  if (&other != this)
  {
    this->id_ = other.id_;
    this->spawnRate_ = other.spawnRate_;
    this->currentSprite_ = other.currentSprite_;
    this->pos_ = other.pos_;
    this->size_ = other.size_;
    this->sprites_ = other.sprites_;
    this->type = other.type;
  }
  return *this;
}

ABonus::~ABonus()
{

}

void ABonus::collideBonus(AEntity *player)
{
  (void) player;
}

int ABonus::getSpawnRate() const
{
  return this->spawnRate_;
}

void ABonus::tick(Map &map)
{
  this->move(-1, 0);
  (void) map;
}

const std::string &ABonus::getType() const
{
  return this->type;
}
