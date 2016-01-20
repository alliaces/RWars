#include "EntityContainer.h"

EntityContainer::EntityContainer(const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> &entities)
{
  this->players_ = entities.find("Player")->second;
  this->blocks_ = entities.find("Block")->second;
  this->shots_ = entities.find("Shot")->second;
  this->monsters_ = entities.find("Monster")->second;
  this->explosions_ = entities.find("Explosion")->second;
  this->bonus_= entities.find("Bonus")->second;
}

EntityContainer::~EntityContainer()
{

}

AEntity *EntityContainer::getOneEntity(int id) const
{
  for (std::vector<std::pair<AEntity *, LOADER>>::const_iterator it = this->players_.begin(); it != this->players_.end(); it++)
  {
    if ((*it).first->getIdGlobal() == id)
      return (*it).second->creator();
  }
  for (std::vector<std::pair<AEntity *, LOADER>>::const_iterator it = this->blocks_.begin(); it != this->blocks_.end(); it++)
  {
    if ((*it).first->getIdGlobal() == id)
      return (*it).second->creator();
  }
  for (std::vector<std::pair<AEntity *, LOADER>>::const_iterator it = this->shots_.begin(); it != this->shots_.end(); it++)
  {
    if ((*it).first->getIdGlobal() == id)
      return (*it).second->creator();
  }
  for (std::vector<std::pair<AEntity *, LOADER>>::const_iterator it = this->monsters_.begin(); it != this->monsters_.end(); it++)
  {
    if ((*it).first->getIdGlobal() == id)
      return (*it).second->creator();
  }
  for (std::vector<std::pair<AEntity *, LOADER>>::const_iterator it = this->explosions_.begin(); it != this->explosions_.end(); it++)
  {
    if ((*it).first->getIdGlobal() == id)
      return (*it).second->creator();
  }
  for (std::vector<std::pair<AEntity *, LOADER>>::const_iterator it = this->bonus_.begin(); it != this->bonus_.end(); it++)
  {
    if ((*it).first->getIdGlobal() == id)
      return (*it).second->creator();
  }
	return NULL;
}

AEntity *EntityContainer::getOnePlayer() const
{
  int r = rand() % this->players_.size();
  return this->players_[r].second->creator();
}

AEntity *EntityContainer::getOneBlock() const
{
  if (this->blocks_.size() == 0)
    return NULL;
  int r = rand() % this->blocks_.size();
  return this->blocks_[r].second->creator();
}

AEntity *EntityContainer::getOneShot() const
{
  if (this->shots_.size() == 0)
    return NULL;
  int r = rand() % this->shots_.size();
  return this->shots_[r].second->creator();
}

AEntity *EntityContainer::getOneMonster() const
{
  if (this->monsters_.size() == 0)
    return NULL;

  unsigned int r = rand() % this->monsters_.size();
  int rate = rand() % 99 + 1;
  unsigned int i = 0;

  while (i < this->monsters_.size())
  {
    if (static_cast<AMonster *>(this->monsters_[r].first)->getSpawnRate() > rate)
      break;
    ++r;
    if (r == this->monsters_.size())
      r = 0;
    ++i;
  }
  return this->monsters_[r].second->creator();
}

AEntity *EntityContainer::getOneExplosion() const
{
  if (this->explosions_.size() == 0)
    return NULL;
  int r = rand() % this->explosions_.size();
  return this->explosions_[r].second->creator();
}

AEntity *EntityContainer::getOneBonus() const
{
  if (this->bonus_.size() == 0)
    return NULL;
  unsigned int r = rand() % this->bonus_.size();
  int rate = rand() % 99 + 1;
  unsigned int i = 0;
  while (i < this->bonus_.size())
  {
    if (static_cast<ABonus *>(this->bonus_[r].first)->getSpawnRate() > rate)
      break;
    ++r;
    if (r == this->bonus_.size())
      r = 0;
    ++i;
  }
  return this->bonus_[r].second->creator();
}
