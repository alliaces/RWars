#ifndef SIMPLE_PACKET_H_
#define SIMPLE_PACKET_H_

#include <string>
#include "APacket.h"

class SimplePacket : public APacket
{
public:
  SimplePacket(int);
  ~SimplePacket();

  char *build();
};

#endif
