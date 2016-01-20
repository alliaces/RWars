#include "ABlock.h"

ABlock::ABlock(int health, bool isDestructible ,int width, int height) : AEntity(width, height)
{
  this->health_ = health;
  this->isCollidable_ = true;
  this->isDestructible_ = isDestructible;
  this->type = "Block";
}

ABlock::ABlock(const ABlock &other) : AEntity(other)
{
  this->health_ = other.health_;
  this->isDestructible_ = other.isDestructible_;
  this->type = other.type;
  this->isCollidable_ = other.isCollidable_;
}

ABlock &ABlock::operator=(const ABlock &other)
{
  if (&other != this)
  {
    this->id_ = other.id_;
    this->currentSprite_ = other.currentSprite_;
    this->isCollidable_ = other.isCollidable_;
    this->health_ = other.health_;
    this->isDestructible_ = other.isDestructible_;
    this->pos_ = other.pos_;
    this->size_ = other.size_;
    this->sprites_ = other.sprites_;
    this->type = other.type;
  }
  return *this;
}

ABlock::~ABlock()
{

}

bool ABlock::isCollidable() const
{
  return this->isCollidable_;
}

int ABlock::getHealth() const
{
  return this->health_;
}

void ABlock::takeDmg(int dmgTaken)
{
    if (dmgTaken > 0 && this->isDestructible_ == true)
    {
      this->health_ -= dmgTaken;
      if (this->health_ < 0)
        this->health_ = 0;
    }
}

void ABlock::tick(Map &map)
{
  this->move(-1, 0);
  (void) map;
}

const std::string &ABlock::getType() const
{
  return this->type;
}
