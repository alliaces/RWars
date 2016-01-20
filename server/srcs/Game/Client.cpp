#include "Client.h"

ClientGame::ClientGame(int idPlayer, int idClient, const std::string &name, ISocket *sock)
{
  this->idPlayer_ = idPlayer;
  this->idClient_ = idClient;
  this->sock_ = sock;
  this->isReady_ = false;
  this->name_ = name;
  this->score_ = 0;
  this->entity_ = NULL;
}

ClientGame::~ClientGame()
{

}

bool ClientGame::isReady() const
{
  return this->isReady_;
}

int ClientGame::getIdPlayer() const
{
  return this->idPlayer_;
}

ISocket *ClientGame::getSock() const
{
  return this->sock_;
}

void ClientGame::setIdPlayer(int id)
{
  this->idPlayer_ = id;
}

const std::string &ClientGame::getName() const
{
  return this->name_;
}

int ClientGame::getIdClient() const
{
  return this->idClient_;
}

int ClientGame::getScore() const
{
  return this->score_;
}

int *ClientGame::getPScore()
{
  return &score_;
}

void ClientGame::setScore(int score)
{
  this->score_ += score;
}

void ClientGame::setEntity(AEntity *entity)
{
  this->entity_ = entity;
}

AEntity *ClientGame::getEntity() const
{
  return this->entity_;
}

void ClientGame::setIdEntity(int id)
{
  this->entity_->setId(id);
}

void ClientGame::ready(bool b)
{
  this->isReady_ = b;
}

ClientServer::ClientServer(int idClient, const std::string &name)
{
  this->idClient_ = idClient;
  this->name_ = name;
  this->room_ = "";
}

ClientServer::~ClientServer()
{

}

const std::string &ClientServer::getRoom() const
{
  return this->room_;
}

const std::string &ClientServer::getName() const
{
  return this->name_;
}

int ClientServer::getIdClient() const
{
  return this->idClient_;
}

void ClientServer::setRoom(const std::string &room)
{
  this->room_ = room;
}
