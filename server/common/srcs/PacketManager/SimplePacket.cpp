#include "SimplePacket.h"

SimplePacket::SimplePacket(int op) : APacket(op) { }

SimplePacket::~SimplePacket() { }

char *SimplePacket::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  return (packet);
}
