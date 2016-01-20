#include "Map.h"
#include "EntityContainer.h"
#include "AEntity.h"

Map::Map() : std::vector<AEntity *>()
{
}

Map::~Map()
{

}

void Map::start(void *container, int *id)
{
  this->container_ = static_cast<EntityContainer *>(container);
  this->currentId_ = id;
}

void *Map::createEntity(int id)
{
  AEntity *tmp = this->container_->getOneEntity(id);
  if (tmp == NULL)
    return NULL;
  tmp->setId(*currentId_);
  *currentId_ += 1;
  this->push_back(tmp);
  return tmp;
}
