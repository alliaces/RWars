#include "StringPacket.h"

StringPacket::StringPacket(int op, const std::string& str) : APacket(op)
{
  size_ = HEADER_SIZE + 1;
  this->setString(str);
}

StringPacket::~StringPacket() { }

void StringPacket::setString(const std::string& str)
{
  str_ = str;
  size_ = HEADER_SIZE + str_.length() + 1;
}

const std::string& StringPacket::getString() const
{
  return (str_);
}

char *StringPacket::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, str_.c_str(), str_.length() + 1);
  return (packet);
}
