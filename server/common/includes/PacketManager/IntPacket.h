#ifndef INT_PACKET_H_
#define INT_PACKET_H_

#include "APacket.h"

class IntPacket : public APacket
{
public:
  IntPacket(int, int);
  ~IntPacket();

  void setInt(int);
  int getInt() const;

  char *build();
private:
  const int SIZE = 12;

  int i_;
};

#endif
