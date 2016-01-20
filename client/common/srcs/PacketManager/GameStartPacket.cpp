#include "GameStartPacket.h"

GameStartPacket::GameStartPacket(const std::string& ip, int port) : APacket(Packet::START_GAME)
{
  size_ = HEADER_SIZE + 4 + 1;
  this->setIp(ip);
  this->setPort(port);
}

GameStartPacket::~GameStartPacket() { }

void GameStartPacket::setIp(const std::string& ip)
{
  ip_ = ip;
  size_ = HEADER_SIZE + 4 + ip_.length() + 1;
}

void GameStartPacket::setPort(int port)
{
  port_ = port;
}

const std::string& GameStartPacket::getIp() const
{
  return (ip_);
}

int GameStartPacket::getPort() const
{
  return (port_);
}

char *GameStartPacket::build()
{
  char *packet = new char[size_];
  int n = 8 + ip_.length() + 1;
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, ip_.c_str(), ip_.length() + 1);
  std::memcpy(packet + n, &port_, 4);
  return (packet);
}
