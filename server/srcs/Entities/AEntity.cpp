#include "AEntity.h"

AEntity::AEntity(int width, int height)
{
  this->updateTimer_ = 0;
  this->id_ = -1;
  this->idGlobal_ = -1;
  this->currentSprite_ = 0;
  this->isCreate_ = false;
  this->tickOverride_ = false;
  this->pos_ = Vector2(-1, -1);
  this->size_ = Vector2(width, height);
}

AEntity::AEntity(const AEntity &other)
{
  this->updateTimer_ = 0;
  this->id_ = other.id_;
  this->currentSprite_ = other.currentSprite_;
  this->pos_ = other.pos_;
  this->size_ = other.size_;
  this->sprites_ = other.sprites_;
  this->idGlobal_ = other.idGlobal_;
  this->isCreate_ = other.isCreate_;
  this->tickOverride_ = other.tickOverride_;
}

AEntity &AEntity::operator=(const AEntity &other)
{
  if (&other != this)
  {
    this->updateTimer_ = 0;
    this->id_ = other.id_;
    this->pos_ = other.pos_;
    this->size_ = other.size_;
    this->sprites_ = other.sprites_;
    this->idGlobal_ = other.idGlobal_;
    this->isCreate_ = other.isCreate_;
    this->tickOverride_ = other.tickOverride_;
  }
  return *this;
}

AEntity::~AEntity()
{

}

bool AEntity::allowSendUpdate(int time)
{
  this->updateTimer_ += 1;
  if (this->updateTimer_ < time)
    return (false);
  this->updateTimer_ = 0;
  return (true);
}

bool AEntity::isTickOverride() const
{
  return this->tickOverride_;
}

bool AEntity::isCreate() const
{
  return this->isCreate_;
}

void AEntity::create()
{
  this->isCreate_ = true;
}

int AEntity::getId() const
{
  return this->id_;
}

void AEntity::setId(int id)
{
  this->id_ = id;
}

int AEntity::getIdGlobal() const
{
  return this->idGlobal_;
}

const Vector2 &AEntity::getOldPos() const
{
  return this->oldPos_;
}

const Vector2 &AEntity::getPos() const
{
  return this->pos_;
}

int AEntity::getPosX() const
{
  return this->pos_.x;
}

int AEntity::getPosY() const
{
  return this->pos_.y;
}

void AEntity::setPos(const Vector2 &pos)
{
  this->pos_.x = pos.x;
  this->pos_.y = pos.y;
}

void AEntity::moveToOld()
{
  this->pos_.x = this->oldPos_.x;
  this->pos_.y = this->oldPos_.y;
}

void AEntity::move(int x, int y)
{
  this->oldPos_.x = this->pos_.x;
  this->oldPos_.y = this->pos_.y;
  this->pos_.x += x;
  this->pos_.y += y;
}

void AEntity::setSize(const Vector2 &size)
{
  this->size_ = size;
}

const Vector2 &AEntity::getSize() const
{
  return this->size_;
}

int AEntity::getWidth() const
{
  return this->size_.x;
}

int AEntity::getHeight() const
{
  return this->size_.y;
}

void AEntity::addSprite(int id)
{
  this->sprites_.push_back(id);
}

const std::vector<int> &AEntity::getAllSprites() const
{
  return this->sprites_;
}

int AEntity::getOneSprite(int index) const
{
  return this->sprites_[index];
}

int AEntity::getCurrentSprite() const
{
  return this->sprites_[this->currentSprite_];
}

bool AEntity::isColliding(const AEntity &other) const
{
if ((this->pos_.y + this->size_.y <= other.pos_.y) || (this->pos_.y >= other.pos_.y + other.size_.y))
  return false;
if ((this->pos_.x + this->size_.x <= other.pos_.x) || (this->pos_.x >= other.pos_.x + other.size_.x))
  return false;
return true;
}
