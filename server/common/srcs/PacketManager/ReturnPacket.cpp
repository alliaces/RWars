#include "ReturnPacket.h"

ReturnPacket::ReturnPacket(int opcode, const std::string& error) : APacket(Packet::RETURN)
{
  size_ = HEADER_SIZE + 4 + 1;
  this->setClientOpcode(opcode);
  this->setError(error);
}

ReturnPacket::~ReturnPacket() { }

void ReturnPacket::setClientOpcode(int op)
{
  clientOpcode_ = op;
}

void ReturnPacket::setError(const std::string& error)
{
  error_ = error;
  size_ = HEADER_SIZE + 4 + error_.length() + 1;
}

int ReturnPacket::getClientOpcode() const
{
  return (clientOpcode_);
}

const std::string& ReturnPacket::getError() const
{
  return (error_);
}

char *ReturnPacket::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, &clientOpcode_, 4);
  std::memcpy(packet + 12, error_.c_str(), error_.length() + 1);
  return (packet);
}
