#include "APacket.h"

APacket::APacket(int op)
{
  opcode_ = op;
  size_ = HEADER_SIZE;
}

void APacket::setOpcode(int op)
{
  opcode_ = op;
}

void APacket::setClientId(int id)
{
  clientId_ = id;
}

int APacket::getOpcode() const
{
  return (opcode_);
}

int APacket::getSize() const
{
  return (size_);
}

int APacket::getClientId() const
{
  return (clientId_);
}
