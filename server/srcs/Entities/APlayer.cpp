#include "APlayer.h"

APlayer::APlayer(int health, int dmg, int width, int height, const std::string &name) : AEntity(width, height)
{
  this->health_ = health;
  this->maxHealth_ = health;
  this->dmg_ = dmg;
  this->name_ = name;
  this->shoot_ = 40;
  this->refreshShoot_ = 40;
  this->orientation_ = 8;
  this->speed_ = 1;
  this->isDead_ = false;
  this->type = "Player";
  this->shotEntity_ = -1;
  this->score_ = NULL;
  this->move_[0] = &APlayer::up;
  this->move_[1] = &APlayer::ne;
  this->move_[2] = &APlayer::right;
  this->move_[3] = &APlayer::se;
  this->move_[4] = &APlayer::down;
  this->move_[5] = &APlayer::sw;
  this->move_[6] = &APlayer::left;
  this->move_[7] = &APlayer::nw;
  this->move_[8] = &APlayer::nope;
}

APlayer::APlayer(const APlayer &other) : AEntity(other)
{
  this->health_ = other.health_;
  this->score_ = other.score_;
  this->speed_ = other.speed_;
  this->refreshShoot_ = other.refreshShoot_;
  this->dmg_ = other.dmg_;
  this->maxHealth_ = other.maxHealth_;
  this->name_ = other.name_;
  this->shoot_ = other.shoot_;
  this->orientation_ = other.orientation_;
  this->move_ = other.move_;
  this->isDead_ = other.isDead_;
  this->type = other.type;
  this->shotEntity_ = other.shotEntity_;
}

APlayer &APlayer::operator=(const APlayer &other)
{
  if (&other != this)
  {
    this->id_ = other.id_;
    this->speed_ = other.speed_;
    this->score_ = other.score_;
    this->refreshShoot_ = other.refreshShoot_;
    this->currentSprite_ = other.currentSprite_;
    this->maxHealth_ = other.maxHealth_;
    this->orientation_ = other.orientation_;
    this->health_ = other.health_;
    this->dmg_ = other.dmg_;
    this->shoot_ = other.shoot_;
    this->name_ = other.name_;
    this->pos_ = other.pos_;
    this->size_ = other.size_;
    this->sprites_ = other.sprites_;
    this->move_ = other.move_;
    this->isDead_ = other.isDead_;
    this->type = other.type;
    this->shotEntity_ = other.shotEntity_;
  }
  return *this;
}

APlayer::~APlayer()
{

}

void APlayer::dead()
{
  this->isDead_ = true;
}

void APlayer::heal(int health)
{
  this->health_ += health;
  if (this->health_ > this->maxHealth_)
    this->health_ = this->maxHealth_;
  if (this->health_ < 0)
    this->health_ = 0;
}

bool APlayer::isDead() const
{
  return this->isDead_;
}

int APlayer::getMaxHealth() const
{
  return this->maxHealth_;
}

int APlayer::getDmg() const
{
  return this->dmg_;
}

void APlayer::setDmg(int dmg)
{
  this->dmg_ = dmg;
}

int APlayer::getHealth() const
{
  return this->health_;
}

int APlayer::getOrientation() const
{
  return this->orientation_;
}

void APlayer::setOrientation(int o)
{
  this->orientation_ = o;
}

int APlayer::getShoot() const
{
  return this->shoot_;
}

void APlayer::refreshShoot()
{
  this->shoot_ = this->refreshShoot_;
}

void APlayer::setRefreshShoot(int r)
{
  this->refreshShoot_ = r;
}

int APlayer::getShotEntity() const
{
  return this->shotEntity_;
}

const std::string &APlayer::getName() const
{
  return this->name_;
}

int APlayer::getSpeed() const
{
  return this->speed_;
}

void APlayer::setSpeed(int speed)
{
  this->speed_ = speed;
}

void APlayer::takeDmg(int dmgTaken)
{
  if (dmgTaken > 0)
  {
    this->health_ -= dmgTaken;
    if (this->health_ < 0)
      this->health_ = 0;
  }
}

int APlayer::getScore() const
{
  if (this->score_ != NULL)
    return *score_;
  return 0;
}

void APlayer::addScore(int score)
{
  if (this->score_ != NULL)
    *score_ += score;
}

void APlayer::setScore(int *pScore)
{
  this->score_ = pScore;
}

void APlayer::up()
{
  if (this->pos_.y - 22 < 0)
    this->down();
  else
    this->move(0 * this->speed_, -1 * this->speed_);
}

void APlayer::ne()
{
  if (this->pos_.x + this->size_.x + 1 > 1280 || this->pos_.y - 21 < 0)
    this->up();
  else
    this->move(1 * this->speed_, -1 * this->speed_);
}

void APlayer::right()
{
  if (this->pos_.x + this->size_.x + 2 > 1280)
    this->left();
  else
    this->move(1 * this->speed_, 0 * this->speed_);
}

void APlayer::se()
{
  if (this->pos_.x + this->size_.x + 1 > 1280 || this->pos_.y + this->size_.y + 1 > 720)
    this->down();
  else
    this->move(1 * this->speed_, 1 * this->speed_);
}

void APlayer::down()
{
  if (this->pos_.y + this->size_.y + 2 > 720)
    this->up();
  else
    this->move(0 * this->speed_, 1 * this->speed_);
}

void APlayer::sw()
{
  if (this->pos_.x - 2 < 0 || this->pos_.y + this->size_.y + 1 > 720)
    this->down();
  else
    this->move(-1 * this->speed_, 1 * this->speed_);
}

void APlayer::left()
{
  if (this->pos_.x - 2 < 0)
    this->right();
  else
    this->move(-2 * this->speed_, 0 * this->speed_);
}

void APlayer::nw()
{
  if (this->pos_.x - 2 < 0 || this->pos_.y - 21 < 0)
    this->up();
  else
    this->move(-1 * this->speed_, -1 * this->speed_);
}

void APlayer::nope()
{
  this->move(0 * this->speed_, 0 * this->speed_);
}

void APlayer::tick(Map &map)
{
  (void) map;
  if (this->shoot_ > 0)
    --this->shoot_;
  if (this->move_.find(this->orientation_) != this->move_.end())
    (this->*move_[this->orientation_])();
}

const std::string &APlayer::getType() const
{
  return this->type;
}
