#include "AShot.h"

AShot::AShot(int speed, int width, int height) : AEntity(width, height)
{
    this->speed_ = speed;
    this->dmg_ = 5;
    this->orientation_ = -1;
    this->idOwner_ = 56;
    this->type = "Shot";
}

AShot::AShot(const AShot &other) : AEntity(other)
{
  this->speed_ = other.speed_;
  this->dmg_ = other.dmg_;
  this->orientation_ = other.orientation_;
  this->type = other.type;
}

AShot &AShot::operator=(const AShot &other)
{
  if (&other != this)
  {
    this->id_ = other.id_;
    this->currentSprite_ = other.currentSprite_;
    this->orientation_ = other.orientation_;
    this->speed_ = other.speed_;
    this->dmg_ = other.dmg_;
    this->pos_ = other.pos_;
    this->size_ = other.size_;
    this->sprites_ = other.sprites_;
    this->type = other.type;
  }
  return *this;
}

AShot::~AShot()
{

}

int AShot::getDmg() const
{
  return this->dmg_;
}

int AShot::getOrientation() const
{
  return this->orientation_;
}

int AShot::getIdOwner() const
{
  return this->idOwner_;
}

void AShot::setIdOwner(int id)
{
  this->idOwner_ = id;
}

void AShot::shoot(int id, int dmg, int o)
{
  this->idOwner_ = id;
  this->orientation_ = o;
  this->setDmg(dmg);
}

void AShot::setDmg(int newDmg)
{
  this->dmg_ = newDmg;
}

void AShot::tick(Map &map)
{
  (void) map;
  this->move(this->speed_ * this->orientation_, 0);
}

const std::string &AShot::getType() const
{
  return this->type;
}
