#include "Game.h"

Game::Game(const std::string &name, const std::string &ip, int port, EntityContainer *container)
{
  this->name_ = name;
  this->net_ = NULL;
  this->game_ = false;
  this->isFinished_ = false;
  this->ip_ = ip;
  this->port_ = port;
  this->currentId_ = 4;
  this->nbMonsters_ = 5;
  this->timerMonster_ = 200;
  this->timerBlock_ = 400;
  this->container_ = container;
  this->events_[Packet::UPDATE_POS] = &Game::handlePos;
  this->events_[Packet::PLAYER_SHOT] = &Game::handleShoot;
  this->events_[Packet::PLAYER_SCORE] = &Game::handleScore;
  this->events_[Packet::ROOM_BACK] = &Game::handleLobby;
  this->events_[Packet::AUTH] = &Game::handleAuth;
  this->events_[Packet::ENTITY_CREATE] = &Game::handleCreate;
  this->collisions_["Block"] = &Game::collisionBlock;
  this->collisions_["Shot"] = &Game::collisionShot;
  this->collisions_["Bonus"] = &Game::collisionBonus;
  this->collisions_["Explosion"] = &Game::collisionExplosion;
  this->collisions_["Monster"] = &Game::collisionMonster;
  this->collisions_["Player"] = &Game::collisionPlayer;
  this->currentIdClient_ = 0;
  this->map_ = Map();
}

Game::~Game()
{
  if (this->container_)
    delete this->container_;
}

void Game::initGame()
{
  this->map_.start(this->container_, &this->currentId_);
  this->net_ = new SNetManager(this, protocolId::UDP, this->port_);
  this->game_ = true;
  this->nbMonsters_ = 5 + (this->getNbClients() * 1.5);
  this->timerMonster_ = 200 / this->getNbClients();
  this->clients_.clear();
  this->update();
}

void Game::update()
{
  while (this->game_ == true)
  {
    this->endGame();
    this->checkMap();
    this->checkCollisions();
    this->checkExplosion();
    this->checkMonster();
    this->checkPlayer();
    this->checkBlock();
    this->checkCreate();
    this->net_->update(0.003);
    #ifndef _WIN32
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    #else
        Sleep(3);
    #endif
  }
  this->theEnd();
}

void Game::theEnd()
{
  std::cout << "The End" << std::endl; //DEBUG
  this->game_ = true;
  this->sendFinalScore();
  this->game_ = false;
  this->clients_.clear();
  this->map_.clear();
  this->isFinished_ = true;
}

void Game::sendFinalScore()
{
  for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    Vector2Packet *ret = new Vector2Packet(Packet::FINAL_SCORE , Vector2(it->second->getEntity()->getId(), it->second->getScore()));
    ret->setClientId(it->second->getIdClient());
    this->net_->doEvent(Event::PACKET, ret);
    this->net_->update(0.5);
    Vector2Packet *tmp = new Vector2Packet(Packet::FINAL_SCORE , Vector2(it->second->getEntity()->getId(), it->second->getScore()));
    tmp->setClientId(it->second->getIdClient());
    this->net_->doEvent(Event::PACKET, tmp);
    this->net_->update(0.05);
  }
}

void Game::endGame()
{
  int deaths = 0;

  for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    if (static_cast<APlayer *>(it->second->getEntity())->isDead() == true)
      ++deaths;
  }
  if (deaths != 0 && deaths == this->getNbClients())
    this->game_ = false;
}

void Game::checkCollisions()
{
   unsigned int i = 0;
   unsigned int j = 0;

   while (i < this->map_.size())
   {
     j = 0;
     while (j < this->map_.size())
     {
       if (i != j)
        if (this->map_[i]->isColliding(*(this->map_[j])))
        {
	        (this->*collisions_[this->map_[i]->getType()])(this->map_[i], this->map_[j]);
          break;
        }
       ++j;
     }
     ++i;
   }
 }

void Game::collisionShot(AEntity *a, AEntity *b)
{
  if (b->getType() == "Monster")
  {
    static_cast<AMonster *>(b)->takeDmg(static_cast<AShot *>(a)->getDmg());
    this->setPlayerScore(static_cast<AShot *>(a)->getIdOwner(), static_cast<AMonster *>(b)->getMaxHealth());
  }
  if (b->getType() == "Player")
  {
    if (static_cast<AShot *>(a)->getIdOwner() > 3 && static_cast<APlayer *>(b)->isDead() == false)
    {
      static_cast<APlayer *>(b)->takeDmg(static_cast<AShot *>(a)->getDmg());
      Vector2 client = findClientEntity(b);
      Vector2Packet *ret = new Vector2Packet(Packet::ENTITY_LIFE , Vector2(client.x, static_cast<APlayer *>(b)->getHealth()));
      ret->setClientId(client.y);
      this->net_->doEvent(Event::PACKET, ret);
    }
    else
      return;
  }
  if (b->getType() == "Block")
  {
    if (static_cast<ABlock *>(b)->isCollidable() == true)
      static_cast<ABlock *>(b)->takeDmg(static_cast<AShot *>(a)->getDmg());
  }
  if (b->getType() == "Shot")
  {
    this->sendDestroyEntity(b->getId());
    this->map_.erase(std::find(this->map_.begin (),this->map_.end (), b));
  }
  if (b->getType() == "Explosion" || b->getType() == "Bonus")
    return;
  this->sendDestroyEntity(a->getId());
  AExplosion *tmp = static_cast<AExplosion *>(this->container_->getOneExplosion());
  if (tmp != NULL)
  {
    tmp->setId(this->currentId_++);
    tmp->setSize(Vector2(a->getHeight(), a->getHeight()));
    tmp->move(a->getPosX(), a->getPosY());
    this->map_.push_back(tmp);
    this->sendCreateEntity(tmp, "");
  }
  this->map_.erase(std::find(this->map_.begin (),this->map_.end (), a));
}

void Game::collisionExplosion(AEntity *a, AEntity *b)
{
  (void) a;
  (void) b;
}

void Game::collisionPlayer(AEntity *a, AEntity *b)
{
  if (static_cast<APlayer *>(a)->isDead() == true)
    return;
  if (b->getType() == "Player")
    if (static_cast<APlayer *>(b)->isDead() == true)
      return;
  if (b->getType() == "Shot")
  {
    this->collisionShot(b, a);
    return;
  }
  if (b->getType() == "Monster")
  {
    static_cast<APlayer *>(a)->takeDmg(1);
    static_cast<AMonster *>(b)->takeDmg(1);
    Vector2 client = findClientEntity(a);
    Vector2Packet *ret = new Vector2Packet(Packet::ENTITY_LIFE , Vector2(client.x, static_cast<APlayer *>(a)->getHealth()));
    ret->setClientId(client.y);
    this->net_->doEvent(Event::PACKET, ret);
    a->moveToOld();
    b->moveToOld();
    return;
  }
  if (b->getType() == "Explosion")
    return;
  if (b->getType() == "Bonus")
  {
    this->collisionBonus(b, a);
    return;
  }
  if (b->getType() == "Block")
  {
    static_cast<APlayer *>(a)->takeDmg(1);
    static_cast<ABlock *>(b)->takeDmg(1);
    Vector2 client = findClientEntity(a);
    Vector2Packet *ret = new Vector2Packet(Packet::ENTITY_LIFE , Vector2(client.x, static_cast<APlayer *>(a)->getHealth()));
    ret->setClientId(client.y);
    this->net_->doEvent(Event::PACKET, ret);
    a->moveToOld();
    b->moveToOld();
    return;
  }
}

void Game::collisionMonster(AEntity *a, AEntity *b)
{
  if (b->getType() == "Player")
  {
    this->collisionPlayer(b, a);
    return;
  }
  if (b->getType() == "Shot")
  {
    this->collisionShot(b, a);
    return;
  }
  if (b->getType() == "Block")
  {
    this->collisionBlock(b, a);
    return;
  }
  if (b->getType() == "Explosion" || b->getType() == "Bonus" || b->getType() == "Monster")
    return;
}

void Game::collisionBlock(AEntity *a, AEntity *b)
{
  if (static_cast<ABlock *>(a)->isCollidable() == false)
    return;
  if (b->getType() == "Player")
  {
    this->collisionPlayer(b, a);
    return;
  }
  if (b->getType() == "Shot")
  {
    this->collisionShot(b, a);
    return;
  }
  if (b->getType() == "Monster")
  {
    static_cast<ABlock *>(a)->takeDmg(1);
    static_cast<AMonster *>(b)->takeDmg(1);
  }
  if (b->getType() == "Explosion" || b->getType() == "Bonus")
    return;
  if (b->getType() == "Block")
  {
    static_cast<ABlock *>(a)->takeDmg(1);
    static_cast<ABlock *>(b)->takeDmg(1);
  }
  a->moveToOld();
  b->moveToOld();
}

void Game::collisionBonus(AEntity *a, AEntity *b)
{
  if (b->getType() == "Player")
  {
    if (static_cast<APlayer *>(b)->isDead() == true)
      return;
    static_cast<ABonus *>(a)->collideBonus(b);
    this->sendDestroyEntity(a->getId());
    Vector2 client = findClientEntity(b);
    Vector2Packet *ret = new Vector2Packet(Packet::ENTITY_LIFE , Vector2(client.x, static_cast<APlayer *>(b)->getHealth()));
    ret->setClientId(client.y);
    this->net_->doEvent(Event::PACKET, ret);
    Vector2Packet *ret2 = new Vector2Packet(Packet::ENTITY_POINT , Vector2(client.x, static_cast<APlayer *>(b)->getScore()));
    ret2->setClientId(client.y);
    this->net_->doEvent(Event::PACKET, ret2);
    this->map_.erase(std::find(this->map_.begin (),this->map_.end (), a));
  }
}

void Game::checkMap()
{
  unsigned int i = 0;

  while (i < this->map_.size())
  {
    if (this->map_[i]->getType() == "Player")
    {
      if (static_cast<APlayer *>(this->map_[i])->isDead() == false)
        {
          this->map_[i]->tick(this->map_);
          this->sendUpdateEntity(this->map_[i]);
        }
    }
    else
    {
      this->map_[i]->tick(this->map_);
      this->sendUpdateEntity(this->map_[i]);
    }
    if ((this->map_[i]->getPosX() + this->map_[i]->getWidth() < -50 || this->map_[i]->getPosX() > 1500 || this->map_[i]->getPosY() < -50 || this->map_[i]->getPosY() > 800) && this->map_[i]->getType() != "Player")
    {
      if (this->map_[i]->getType() == "Monster")
        ++this->nbMonsters_;
      this->sendDestroyEntity(this->map_[i]->getId());
      this->map_.erase(this->map_.begin() + i);
      break;
    }
    ++i;
  }
}

void Game::checkPlayer()
{
  for (std::vector<AEntity *>::iterator it = this->map_.begin(); it != this->map_.end(); it++)
  {
    if ((*it)->getType() == "Player")
    {
      if (static_cast<APlayer *>((*it))->getHealth() == 0 && static_cast<APlayer *>((*it))->isDead() == false)
      {
        static_cast<APlayer *>((*it))->dead();
        Vector2 client = findClientEntity((*it));
        SimplePacket *ret = new SimplePacket(Packet::SPECTATOR);
        ret->setClientId(client.y);
        this->net_->doEvent(Event::PACKET, ret);
        this->sendDestroyEntity((*it)->getId());
        AExplosion *tmp = static_cast<AExplosion *>(this->container_->getOneExplosion());
        if (tmp != NULL)
        {
          tmp->setId(this->currentId_++);
          tmp->setSize(Vector2((*it)->getWidth(), (*it)->getWidth()));
          tmp->move((*it)->getPosX(), (*it)->getPosY());
          this->map_.push_back(tmp);
          this->sendCreateEntity(tmp, "");
        }
        break;
      }
    }
  }
}

void Game::checkExplosion()
{
  for (std::vector<AEntity *>::iterator it = this->map_.begin(); it != this->map_.end(); it++)
  {
    if ((*it)->getType() == "Explosion")
    {
      if (static_cast<unsigned int>((*it)->getCurrentSprite()) == (*it)->getAllSprites().size() - 1 && static_cast<AExplosion *>((*it))->getTimer() == 0)
      {
        this->sendDestroyEntity((*it)->getId());
        this->map_.erase(std::find(this->map_.begin(), this->map_.end(), (*it)));
        break;
      }
    }
  }
}

void Game::createBlock()
{
  int r = rand() % 99 + 1;

  --this->timerBlock_;
  if (this->timerBlock_ == 0)
  {
    this->timerBlock_ = 400;
    if (r < 20)
    {
      ABlock *tmp = static_cast<ABlock *>(this->container_->getOneBlock());
      if (tmp != NULL)
      {
        tmp->setId(this->currentId_++);
        tmp->move(1300, rand() % 620 + 30);
        this->map_.push_back(tmp);
        this->sendCreateEntity(tmp, "");
      }
    }
  }
}

void Game::checkBlock()
{
  unsigned int i = 0;

  this->createBlock();
  while (i < this->map_.size())
  {
    if (this->map_[i]->getType() == "Block")
    {
      if (static_cast<ABlock *>(this->map_[i])->getHealth() == 0)
      {
        this->sendDestroyEntity(this->map_[i]->getId());
        AExplosion *tmp = static_cast<AExplosion *>(this->container_->getOneExplosion());
        if (tmp != NULL)
        {
          tmp->setId(this->currentId_++);
          tmp->setSize(Vector2(this->map_[i]->getWidth(), this->map_[i]->getHeight()));
          tmp->move(this->map_[i]->getPosX(), this->map_[i]->getPosY());
          this->map_.push_back(tmp);
          this->sendCreateEntity(tmp, "");
        }
        this->spawnBonus(this->map_[i]);
        this->map_.erase(std::find(this->map_.begin (),this->map_.end (), this->map_[i]));
        break;
      }
    }
    ++i;
  }
}

void Game::checkCreate()
{
  for (std::vector<AEntity *>::iterator it = this->map_.begin(); it != this->map_.end(); it++)
  {
    if ((*it)->isCreate() == false)
      this->sendCreateEntity((*it), "");
  }
}

void Game::createMonster()
{
  --this->timerMonster_;
  if (this->timerMonster_ == 0)
  {
    if (this->getNbClients() != 0)
      this->timerMonster_ = 200 / this->getNbClients();
    if (this->nbMonsters_ > 0)
    {
      AMonster *tmp = static_cast<AMonster *>(this->container_->getOneMonster());
      if (tmp != NULL)
      {
        tmp->setId(this->currentId_++);
        tmp->move(1300, rand() % 620 + 30);
        this->map_.push_back(tmp);
        this->sendCreateEntity(tmp, tmp->getName());
        --this->nbMonsters_;
      }
    }
  }
}

void Game::checkMonster()
{
  unsigned int i = 0;

  this->createMonster();
  while (i < this->map_.size())
  {
    if (this->map_[i]->getType() == "Monster")
    {
      if (static_cast<AMonster *>(this->map_[i])->getShoot() == 0)
      {
        this->shootMonster(static_cast<AMonster *>(this->map_[i]));
        break;
      }
      if (static_cast<AMonster *>(this->map_[i])->getHealth() == 0)
      {
        ++this->nbMonsters_;
        this->sendDestroyEntity(this->map_[i]->getId());
        AExplosion *tmp = static_cast<AExplosion *>(this->container_->getOneExplosion());
        if (tmp != NULL)
        {
          tmp->setId(this->currentId_++);
          tmp->setSize(Vector2(this->map_[i]->getWidth(), this->map_[i]->getHeight()));
          tmp->move(this->map_[i]->getPosX(), this->map_[i]->getPosY());
          this->map_.push_back(tmp);
          this->sendCreateEntity(tmp, "");
        }
        this->spawnBonus(this->map_[i]);
        this->map_.erase(std::find(this->map_.begin (),this->map_.end (), this->map_[i]));
        break;
      }
    }
    ++i;
  }
}

void Game::spawnBonus(AEntity *e)
{
    int r = rand() % 99 + 1;

    if (r < 30)
    {
      ABonus *tmp = static_cast<ABonus *>(this->container_->getOneBonus());
      if (tmp != NULL)
      {
        tmp->setId(this->currentId_++);
        tmp->move(e->getPosX(), e->getPosY());
        this->map_.push_back(tmp);
        this->sendCreateEntity(tmp, "");
      }
    }
}

void Game::setPlayerScore(int id, int score)
{
  if (id > 3)
    return;
  this->clients_[id]->setScore(score / 2);
  Vector2Packet *ret = new Vector2Packet(Packet::ENTITY_POINT , Vector2(this->clients_[id]->getEntity()->getId(), this->clients_[id]->getScore()));
  ret->setClientId(id);
  this->net_->doEvent(Event::PACKET, ret);

}

const Vector2 Game::findClientEntity(AEntity *e)
{
  Vector2 tmp;

  for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    if (it->second->getEntity() == e)
    {
      tmp.x = it->second->getIdPlayer();
      tmp.y = it->first;
      break;
    }
  }
  return tmp;
}

int Game::getIdClient(int n) const
{
  for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    if (n == 0)
      return it->second->getIdClient();
    --n;
  }
  return -1;
}

bool Game::isPlaying() const
{
  return this->game_;
}

int Game::doEvent(Event::id id, void *data)
{
  if (id == Event::id::CLIENT_DISCONNECT)
  {
    this->handleDisconnect(data);
  }
  else
  {
    IPacket *tmp = static_cast<IPacket *>(data);
    if (this->events_.find(static_cast<Packet::id>(tmp->getOpcode())) != this->events_.end())
      (this->*events_[static_cast<Packet::id>(tmp->getOpcode())])(data);
  }
  return 0;
}

void Game::handlePos(void *data)
{
  Vector3Packet *tmp = static_cast<Vector3Packet *>(data);
  if (static_cast<APlayer *>(this->clients_[tmp->getClientId()]->getEntity())->isDead() == false)
    this->movePlayer(tmp->getClientId(), tmp->getPosition().z);
  //std::cout << "POS" << std::endl;
  delete tmp;
}

void Game::handleShoot(void *data)
{
  SimplePacket *tmp = static_cast<SimplePacket *>(data);
  //std::cout << "SHOOT" << std::endl;
  if (static_cast<APlayer *>(this->clients_[tmp->getClientId()]->getEntity())->isDead() == false)
    if (static_cast<APlayer *>(this->clients_[tmp->getClientId()]->getEntity())->getShoot() == 0)
      this->shootPlayer(tmp->getClientId());
  delete tmp;
}

void Game::handleScore(void *data)
{
  SimplePacket *tmp = static_cast<SimplePacket *>(data);
  //std::cout << "SCORE" << std::endl;
  Vector2Packet *ret = new Vector2Packet(Packet::ENTITY_POINT , Vector2(this->clients_[tmp->getClientId()]->getEntity()->getId(), this->clients_[tmp->getClientId()]->getScore()));
  ret->setClientId(tmp->getClientId());
  this->net_->doEvent(Event::PACKET, ret);
  delete tmp;
}

void Game::handleLobby(void *data)
{
  SimplePacket *tmp = static_cast<SimplePacket *>(data);
  std::cout << "LOBBY" << std::endl;
  static_cast<APlayer *>(this->clients_[tmp->getClientId()]->getEntity())->dead();
  this->sendDestroyEntity(this->clients_[tmp->getClientId()]->getEntity()->getId());
  AExplosion *e = static_cast<AExplosion *>(this->container_->getOneExplosion());
  if (e != NULL)
  {
    e->setId(this->currentId_++);
    e->setSize(Vector2(this->clients_[tmp->getClientId()]->getEntity()->getWidth(), this->clients_[tmp->getClientId()]->getEntity()->getWidth()));
    e->move(this->clients_[tmp->getClientId()]->getEntity()->getPosX(), this->clients_[tmp->getClientId()]->getEntity()->getPosY());
    this->map_.push_back(e);
    this->sendCreateEntity(e, "");
  }
  delete tmp;
}

void Game::handleDisconnect(void *data)
{
  int *tmp = static_cast<int *>(data);
  this->clients_.erase(this->clients_.find(*tmp));
  delete tmp;
}

void Game::handleAuth(void *data)
{
  StringPacket *tmp = static_cast<StringPacket *>(data);
  //std::cout << "AUTH UDP" << std::endl; //DEBUG
  if (this->currentIdClient_ <= 3)
  {
    this->clients_[tmp->getClientId()] = new ClientGame(21, tmp->getClientId(), tmp->getString(), NULL);
    this->clients_[tmp->getClientId()]->setEntity(this->container_->getOnePlayer());
    this->clients_[tmp->getClientId()]->setIdPlayer(this->currentIdClient_);
    this->clients_[tmp->getClientId()]->setIdEntity(this->currentIdClient_);
    this->clients_[tmp->getClientId()]->getEntity()->move(120, 120 + this->currentIdClient_ * 120);
    this->map_.push_back(this->clients_[tmp->getClientId()]->getEntity());
    AEntity *e = this->clients_[tmp->getClientId()]->getEntity();
    static_cast<APlayer *>(e)->setScore(this->clients_[tmp->getClientId()]->getPScore());
    this->sendCreateEntity(e, this->clients_[tmp->getClientId()]->getName());
    Vector2Packet *ret = new Vector2Packet(Packet::ENTITY_LIFE , Vector2(this->currentIdClient_, static_cast<APlayer *>(e)->getHealth()));
    ret->setClientId(tmp->getClientId());
    this->net_->doEvent(Event::PACKET, ret);
    ++this->currentIdClient_;
    for (std::vector<AEntity *>::iterator it = this->map_.begin(); it != this->map_.end(); it++)
      this->sendCreateEntity((*it), "");
  }
  delete tmp;
}

void Game::handleCreate(void *data)
{
  EntityCreatePacket *tmp = static_cast<EntityCreatePacket *>(data);

  AEntity *e = this->findEntityId(tmp->getEntityId());
  if (e == NULL)
  {
    delete tmp;
    return;
  }
  EntityCreatePacket *ret = new EntityCreatePacket(e->getId(), Vector3(e->getPosX(), e->getPosY(), 1), Vector2(e->getWidth(), e->getHeight()), e->getOneSprite(0), "");
  ret->setClientId(tmp->getClientId());
  this->net_->doEvent(Event::PACKET, ret);
  delete tmp;
}

AEntity *Game::findEntityId(int id)
{
  for (std::vector<AEntity *>::iterator it = this->map_.begin(); it != this->map_.end(); it++)
  {
    if ((*it)->getId() == id)
      return (*it);
  }
  return NULL;
}

void Game::movePlayer(int idClient, int o)
{
  APlayer *tmp = static_cast<APlayer *>(this->clients_[idClient]->getEntity());
  tmp->setOrientation(o);
}

void Game::sendUpdateEntity(AEntity *e)
{
  if (e->allowSendUpdate(10))
  {
    for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
	  {
	    EntityUpdatePacket *ret = new EntityUpdatePacket(e->getId(), Vector3(e->getPosX(), e->getPosY()), e->getCurrentSprite());
	    ret->setClientId(it->second->getIdClient());
	    this->net_->doEvent(Event::PACKET, ret);
	  }
  }
}

void Game::sendCreateEntity(AEntity *e, const std::string &name)
{
  for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    EntityCreatePacket *ret = new EntityCreatePacket(e->getId(), Vector3(e->getPosX(), e->getPosY(), 1), Vector2(e->getWidth(), e->getHeight()), e->getOneSprite(0), name);
    ret->setClientId(it->second->getIdClient());
    this->net_->doEvent(Event::PACKET, ret);
  }
  e->create();
}

void Game::sendDestroyEntity(int id)
{
  for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    IntPacket *ret = new IntPacket(Packet::ENTITY_DESTROY, id);
    ret->setClientId(it->second->getIdClient());
    this->net_->doEvent(Event::PACKET, ret);
  }
}

void Game::shootPlayer(int idClient)
{
  APlayer *player = static_cast<APlayer *>(this->clients_[idClient]->getEntity());
  player->refreshShoot();
  AEntity *tmp =this->container_->getOneEntity(player->getShotEntity());
  if (tmp != NULL)
  {
    tmp->setId(this->currentId_++);
    if (tmp->getType() == "Shot")
      static_cast<AShot *>(tmp)->shoot(idClient, static_cast<APlayer *>(player)->getDmg(), 1);
    tmp->move(player->getPosX() + player->getWidth() + 1, player->getPosY() + (player->getHeight() / 2) - (tmp->getHeight() / 2));
    this->map_.push_back(tmp);
    this->sendCreateEntity(tmp, "");
  }
}

void Game::shootMonster(AMonster *monster)
{
  monster->refreshShoot();
  AEntity *tmp =this->container_->getOneEntity(monster->getShotEntity());
  if (tmp != NULL)
  {
    tmp->setId(this->currentId_++);
    if (tmp->getType() == "Shot")
      static_cast<AShot *>(tmp)->shoot(monster->getId(), monster->getDmg(), -1);
    tmp->move(monster->getPosX() - tmp->getWidth() - 3, monster->getPosY() + (monster->getHeight() / 2) - (tmp->getHeight() / 2));
    this->map_.push_back(tmp);
    this->sendCreateEntity(tmp, "");
  }
}

void Game::leave(int idClient)
{
  if (this->clients_.find(idClient) != this->clients_.end())
    this->clients_.erase(this->clients_.find(idClient));
}

void Game::leave(const std::string &name) //TODO : Not Working
{
  for (std::map<int, ClientGame *>::iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    if (it->second->getName() == name)
    {
      this->sendDestroyEntity(it->second->getEntity()->getId());
      unsigned int i = 0;
      for (std::vector<AEntity *>::iterator it2 = this->map_.begin(); it2 != this->map_.end(); it2++)
      {
        if (it->second->getEntity() == *it2)
          this->map_.erase(this->map_.begin() + i);
        ++i;
      }
      this->clients_.erase(it->first);
      return;
    }
  }
}

void Game::ready(int idClient, bool b)
{
  if (this->clients_.find(idClient) != this->clients_.end())
    this->clients_[idClient]->ready(b);
}

int Game::getNbClients() const
{
  return this->clients_.size();
}

int Game::getNbClientsReady() const
{
  int ready = 0;

  for(std::map<int, ClientGame *>::const_iterator it = this->clients_.begin(); it != this->clients_.end(); it++)
  {
    if (it->second->isReady() == true)
      ++ready;
  }
  return ready;
}

const std::string &Game::getIp() const
{
  return this->ip_;
}

int Game::getPort() const
{
  return this->port_;
}

const std::string &Game::getName() const
{
  return this->name_;
}

bool Game::isFinished() const
{
  return this->isFinished_;
}

void Game::join(int idClient, const std::string &name, ISocket *sock)
{
  this->clients_[idClient] = new ClientGame(this->clients_.size() + 1, idClient, name, sock);
}

void *Game::startGame(void *room)
{
  static_cast<Game *>(room)->initGame();
  return NULL;
}
