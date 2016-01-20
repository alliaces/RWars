#include "IntPacket.h"

IntPacket::IntPacket(int op, int i) : APacket(op)
{
  size_ = this->SIZE;
  this->setInt(i);
}

IntPacket::~IntPacket() { }

void IntPacket::setInt(int i)
{
  i_ = i;
}

int IntPacket::getInt() const
{
  return (i_);
}

char *IntPacket::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, &i_, 4);
  return (packet);
}
