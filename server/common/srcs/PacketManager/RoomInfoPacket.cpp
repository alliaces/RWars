#include "RoomInfoPacket.h"

RoomInfoPacket::RoomInfoPacket(const std::string& room, int n, bool available) : APacket(Packet::ROOM_INFO)
{
  size_ = HEADER_SIZE + 4 + 2;
  this->setRoom(room);
  this->setNumberOfPlayers(n);
  this->setAvailable(available);
}

RoomInfoPacket::~RoomInfoPacket() { }

void RoomInfoPacket::setRoom(const std::string& room)
{
  room_ = room;
  size_ = HEADER_SIZE + 4 + room_.length() + 2;
}

void RoomInfoPacket::setNumberOfPlayers(int n)
{
  numberOfPlayers_ = n;
}

void RoomInfoPacket::setAvailable(bool b)
{
  available_ = b;
}

const std::string& RoomInfoPacket::getRoom() const
{
  return (room_);
}

int RoomInfoPacket::getNumberOfPlayers() const
{
  return (numberOfPlayers_);
}

bool RoomInfoPacket::isAvailable() const
{
  return (available_);
}

char *RoomInfoPacket::build()
{
  char *packet = new char[size_];
  int n = 8 + room_.length() + 1;
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, room_.c_str(), room_.length() + 1);
  std::memcpy(packet + n, &numberOfPlayers_, 4);
  std::memcpy(packet + n + 4, &available_, 1);
  return (packet);
}
