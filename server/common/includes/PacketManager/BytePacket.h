#ifndef BYTE_PACKET_H_
#define BYTE_PACKET_H_

#include <string>
#include "APacket.h"

class BytePacket : public APacket
{
public:
  BytePacket(int, char c = 0);
  ~BytePacket();

  void setByte(char);
  char getByte() const;

  char *build();
private:
  const int SIZE = 9;

  char byte_;
};

#endif
