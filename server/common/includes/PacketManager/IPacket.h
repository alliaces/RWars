#ifndef IPACKET_H_
#define IPACKET_H_

# define PACKET_SIZE  4
# define HEADER_SIZE  8

#include "Packet.h"

class IPacket
{
public:
  virtual ~IPacket() { }

  virtual void setOpcode(int) = 0;
  virtual void setClientId(int) = 0;

  virtual int getOpcode() const = 0;
  virtual int getSize() const = 0;
  virtual int getClientId() const = 0;

  virtual char *build() = 0;
protected:
  int size_;
  int opcode_;
  int clientId_;
};

#endif
