#include "BytePacket.h"

 BytePacket::BytePacket(int opcode, char byte) : APacket(opcode)
{
  size_ = this->SIZE;
  this->setByte(byte);
}

 BytePacket::~BytePacket() { }

void BytePacket::setByte(char b)
{
  byte_ = b;
}

char BytePacket::getByte() const
{
  return (byte_);
}

char *BytePacket::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, &byte_, 1);
  return (packet);
}
