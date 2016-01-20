#include "AExplosion.h"

AExplosion::AExplosion(int dmg, int width, int height) : AEntity(width, height)
{
  this->dmg_ = dmg;
  this->type = "Explosion";
}

AExplosion::AExplosion(const AExplosion &other) : AEntity(other)
{
  this->dmg_ = other.dmg_;
  this->timer_ = other.timer_;
  this->type = other.type;
}

AExplosion &AExplosion::operator=(const AExplosion &other)
{
  if (&other != this)
  {
    this->id_ = other.id_;
    this->currentSprite_ = other.currentSprite_;
    this->dmg_ = other.dmg_;
    this->pos_ = other.pos_;
    this->size_ = other.size_;
    this->sprites_ = other.sprites_;
    this->timer_ = other.timer_;
    this->type = other.type;
  }
  return *this;
}

AExplosion::~AExplosion()
{

}

void AExplosion::setTimer()
{
  this->timer_ = 400 / this->sprites_.size();
}

int AExplosion::getDmg() const
{
  return this->dmg_;
}

int AExplosion::getTimer() const
{
  return this->timer_;
}

void AExplosion::tick(Map &map)
{
  (void) map;
  this->move(-1, 0);
  if (this->timer_ != 0)
    --this->timer_;
  else
  {
    if (static_cast<unsigned int>(this->currentSprite_) != this->sprites_.size() - 1)
    {
      ++this->currentSprite_;
      this->timer_ = 400 / this->sprites_.size();
    }
  }
}

const std::string &AExplosion::getType() const
{
  return this->type;
}
