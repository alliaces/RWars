#include "GameManager.h"

static bool run = true;

GameManager::GameManager()
{
  this->events_[Packet::ROOM_CREATE] = &GameManager::handleCreate;
  this->events_[Packet::ROOM_JOIN] = &GameManager::handleJoin;
  this->events_[Packet::AUTH] = &GameManager::handleAuth;
  this->events_[Packet::READY] = &GameManager::handleReady;
  this->events_[Packet::ROOM_LEAVE] = &GameManager::handleLeave;
  this->events_[Packet::ROOM_REFRESH] = &GameManager::handleInfo;
}

GameManager::~GameManager()
{
  if (this->builder_)
    delete this->builder_;
  if (this->eManager_)
    delete this->eManager_;
  this->clients_.clear();
  this->rooms_.clear();
}

void GameManager::start(SNetManager *net, int port, const std::vector<std::string> &ips)
{
  this->net_ = net;
  this->eManager_ = new EntityManager();
  this->eManager_->checkPlugin();
  this->builder_ = new GameBuilder(ips, port);
  this->timerPlugin_ = 120;
  while (run)
  {
    if (this->net_->update(1) == false)
      return;
    this->checkNewPlugins();
    this->checkEndedGames();
  }
  std::cout << "SHUTDOWN SERVER" << std::endl;
}

void GameManager::checkEndedGames()
{
  for (std::map<std::string, Game *>::iterator it = this->rooms_.begin(); it != this->rooms_.end(); it++)
  {
    if (it->second->isFinished() == true)
      {
        for (std::map<int, ClientServer *>::iterator it2 = this->clients_.begin(); it2 != this->clients_.end(); it2++)
        {
          if (it2->second->getRoom() == it->second->getName())
            it2->second->setRoom("");
        }
        this->rooms_.erase(it->first);
        break;
      }
  }
}

void GameManager::checkNewPlugins()
{
  --this->timerPlugin_;
  if (this->timerPlugin_ == 0)
  {
    this->timerPlugin_ = 120;
    this->eManager_->checkPlugin();
  }
}

int GameManager::doEvent(Event::id id, void *data)
{
  if (id == Event::id::CLIENT_DISCONNECT)
    this->handleDisconnect(data);
  else
  {
    IPacket *tmp = static_cast<IPacket *>(data);
    if (this->events_.find(static_cast<Packet::id>(tmp->getOpcode())) != this->events_.end())
      (this->*events_[static_cast<Packet::id>(tmp->getOpcode())])(data);
  }
  return 0;
}

void GameManager::handleCreate(void *data)
{
  StringPacket *tmp = static_cast<StringPacket *>(data);
  this->createRoom(tmp->getString(), tmp->getClientId());
  std::cout << "CREATE" << std::endl; //DEBUG
  delete tmp;
}

void GameManager::handleJoin(void *data)
{
  StringPacket *tmp = static_cast<StringPacket *>(data);
  this->joinRoom(tmp->getString(), tmp->getClientId());
  std::cout << "JOIN" << std::endl; //DEBUG
  delete tmp;
}

void GameManager::handleAuth(void *data)
{
  StringPacket *tmp = static_cast<StringPacket *>(data);
  std::cout << "AUTH" << std::endl; //DEBUG
  this->clients_[tmp->getClientId()] = new ClientServer(tmp->getClientId(), tmp->getString());
  delete tmp;
}

void GameManager::handleReady(void *data)
{
  BytePacket *tmp = static_cast<BytePacket *>(data);
  if (this->clients_[tmp->getClientId()]->getRoom() != "")
  {
    this->rooms_[this->clients_[tmp->getClientId()]->getRoom()]->ready(tmp->getClientId(), tmp->getByte());
    ReturnPacket *ret = new ReturnPacket(Packet::id::READY, "");
    ret->setClientId(tmp->getClientId());
    this->net_->doEvent(Event::PACKET, ret);
    if (this->rooms_[this->clients_[tmp->getClientId()]->getRoom()]->getNbClients() == this->rooms_[this->clients_[tmp->getClientId()]->getRoom()]->getNbClientsReady() && this->rooms_[this->clients_[tmp->getClientId()]->getRoom()]->isPlaying() == false && this->rooms_[this->clients_[tmp->getClientId()]->getRoom()]->getNbClients() != 0)
      this->beginGame(this->clients_[tmp->getClientId()]->getRoom());
  }
  std::cout << "READY" << std::endl; //DEBUG
  delete tmp;
}

void GameManager::handleLeave(void *data)
{
  SimplePacket *tmp = static_cast<SimplePacket *>(data);
  if (this->clients_[tmp->getClientId()]->getRoom() != "")
  {
    this->rooms_[this->clients_[tmp->getClientId()]->getRoom()]->leave(this->clients_[tmp->getClientId()]->getIdClient());
    ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_LEAVE, "");
    ret->setClientId(tmp->getClientId());
    this->net_->doEvent(Event::PACKET, ret);
    this->sendLeaveRoom(this->clients_[tmp->getClientId()]->getRoom(), tmp->getClientId());
    this->clients_[tmp->getClientId()]->setRoom("");
  }
  std::cout << "LEAVE" << std::endl; //DEBUG
  delete tmp;
}

void GameManager::handleDisconnect(void *data)
{
  int *tmp = static_cast<int *>(data);

  std::cout << "DISCONNECT" << std::endl; //DEBUG
  if (this->clients_.find(*tmp) != this->clients_.end())
  {
    if (this->clients_[*tmp]->getRoom() != "" && this->rooms_[this->clients_[*tmp]->getRoom()]->isPlaying() == false)
    {
      this->rooms_[this->clients_[*tmp]->getRoom()]->leave(this->clients_[*tmp]->getIdClient());
      this->sendLeaveRoom(this->clients_[*tmp]->getRoom(), *tmp);
    }
    this->clients_.erase(this->clients_.find(*tmp));
  }
  delete tmp;
}

void GameManager::handleInfo(void *data)
{
  SimplePacket *tmp = static_cast<SimplePacket *>(data);

  std::cout << "ROOM_INFO" << std::endl; //DEBUG
  this->getInfoRooms(tmp->getClientId());
  delete tmp;
}

void GameManager::checkEmptyRoom()
{
  for (std::map<std::string, Game *>::iterator it = this->rooms_.begin(); it != this->rooms_.end(); it++)
  {
    if (it->second->getNbClients() == 0 && it->second->isPlaying() == false)
      {
        this->rooms_.erase(it->first);
        break;
      }
  }
}

void GameManager::beginGame(const std::string &name)
{
  std::cout << "LET'S GO" << std::endl; //DEBUG
  int i = 0;
  int id = 0;

  while (i < 4)
  {
    if ((id = this->rooms_[name]->getIdClient(i)) == -1)
      break;
    GameStartPacket *ret = new GameStartPacket(this->rooms_[name]->getIp(), this->rooms_[name]->getPort());
    ret->setClientId(id);
    this->net_->doEvent(Event::PACKET, ret);
    ++i;
  }
  this->thread_.newThread(&Game::startGame, this->rooms_[name]);
}

void GameManager::createRoom(const std::string &name, int idClient)
{
  if (this->rooms_.find(name) == this->rooms_.end())
  {
    if (this->eManager_->getPlayers().size() == 0)
    {
      ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_CREATE, "ERR_UNREACHABLE");
      ret->setClientId(idClient);
      this->net_->doEvent(Event::PACKET, ret);
      return;
    }
    this->rooms_[name] = this->builder_->createGame(name, this->eManager_->getAllEntities());
    ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_CREATE);
    ret->setClientId(idClient);
    this->net_->doEvent(Event::PACKET, ret);
  }
  else
  {
    ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_CREATE, "ERR_EXISTS");
    ret->setClientId(idClient);
    this->net_->doEvent(Event::PACKET, ret);
  }
}

void GameManager::joinRoom(const std::string &name, int idClient)
{
  if (this->rooms_.find(name) != this->rooms_.end())
  {
    if (this->rooms_[name]->isPlaying() == true)
    {
      ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_JOIN, "ERR_INGAME");
      ret->setClientId(idClient);
      this->net_->doEvent(Event::PACKET, ret);
      return;
    }
    if (this->rooms_[name]->getNbClients() <= 3)
    {
      this->clients_[idClient]->setRoom(name);
      this->rooms_[name]->join(idClient, this->clients_[idClient]->getName(), this->net_->getClient(idClient));
      ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_JOIN);
      ret->setClientId(idClient);
      this->net_->doEvent(Event::PACKET, ret);
      this->sendJoinRoom(name, idClient);
      this->sendRoomJoin(name, idClient);
    }
    else
    {
      ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_JOIN, "ERR_ROOMFULL");
      ret->setClientId(idClient);
      this->net_->doEvent(Event::PACKET, ret);
    }
  }
  else
  {
    ReturnPacket *ret = new ReturnPacket(Packet::id::ROOM_JOIN, "ERR_UNREACHABLE");
    ret->setClientId(idClient);
    this->net_->doEvent(Event::PACKET, ret);
  }
}

void GameManager::sendJoinRoom(const std::string &name, int idClient)
{
  int i = 0;
  int id = 0;

  while (i < 4)
  {
    if ((id = this->rooms_[name]->getIdClient(i)) == -1)
      return;
    if (id != idClient)
    {
      StringPacket *ret = new StringPacket(Packet::id::HAS_JOINED, this->clients_[idClient]->getName());
      ret->setClientId(id);
      this->net_->doEvent(Event::PACKET, ret);
    }
    ++i;
  }
}

void GameManager::sendRoomJoin(const std::string &name, int idClient)
{
  int i = 0;
  int id = 0;

  while (i < 4)
  {
    if ((id = this->rooms_[name]->getIdClient(i)) == -1)
      return;
    StringPacket *ret = new StringPacket(Packet::id::HAS_JOINED, this->clients_[id]->getName());
    ret->setClientId(idClient);
    this->net_->doEvent(Event::PACKET, ret);
    ++i;
  }
}

void GameManager::sendLeaveRoom(const std::string &name, int idClient)
{
  int i = 0;
  int id = 0;

  while (i < 4)
  {
    if ((id = this->rooms_[name]->getIdClient(i)) == -1)
      return;
    StringPacket *ret = new StringPacket(Packet::id::HAS_LEFT, this->clients_[idClient]->getName());
    ret->setClientId(id);
    this->net_->doEvent(Event::PACKET, ret);
    ++i;
  }
}

void GameManager::getInfoRooms(int idClient) const
{
  for(std::map<std::string, Game *>::const_iterator it = this->rooms_.begin(); it != this->rooms_.end(); it++)
  {
    RoomInfoPacket *ret = new RoomInfoPacket("", 1, 1);
    ret->setClientId(idClient);
    ret->setRoom(it->first);
    ret->setNumberOfPlayers(it->second->getNbClients());
    ret->setAvailable(!it->second->isPlaying());
    this->net_->doEvent(Event::PACKET, ret);
  }
}
