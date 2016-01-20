#include "GameBuilder.h"

GameBuilder::GameBuilder(const std::vector<std::string> &ips, int port)
{
  this->ips_ = ips;
  this->port_ = port;
  this->currentIp_ = 0;
}

GameBuilder::~GameBuilder()
{

}

Game *GameBuilder::createGame(const std::string &name, const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> &entities, unsigned int nIp)
{
  ++this->port_;
  if (this->ips_.size() == 0)
    return new Game(name, "127.0.0.1", this->port_, new EntityContainer(entities));
  if (nIp >= this->ips_.size())
    return new Game(name, this->ips_[0], this->port_, new EntityContainer(entities));
  return new Game(name, this->ips_[nIp], this->port_, new EntityContainer(entities));
}

Game *GameBuilder::createGame(const std::string &name, const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> &entities)
{
  ++this->port_;
  ++this->currentIp_;
  if (this->ips_.size() == 0)
    return new Game(name, "127.0.0.1", this->port_, new EntityContainer(entities));
  if (this->currentIp_ >= this->ips_.size())
    this->currentIp_ = 0;
  return new Game(name, this->ips_[this->currentIp_], this->port_, new EntityContainer(entities));
}
