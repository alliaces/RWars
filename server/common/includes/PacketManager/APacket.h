#ifndef APACKET_H_
#define APACKET_H_

#include <cstring>
#include "IPacket.h"

class APacket : public IPacket
{
public:
  APacket(int);
  virtual ~APacket() { }

  void setOpcode(int);
  void setClientId(int);

  int getOpcode() const;
  int getSize() const;
  int getClientId() const;

  virtual char *build() = 0;
};

#endif
