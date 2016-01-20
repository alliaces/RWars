#ifndef VECTOR2_PACKET_H_
#define VECTOR2_PACKET_H_

#include <string>
#include "APacket.h"
#include "Vector2.h"

class Vector2Packet : public APacket
{
public:
  Vector2Packet(int, const Vector2&);
  ~Vector2Packet();

  void setPosition(const Vector2&);
  const Vector2& getPosition() const;

  char *build();
private:
  const int SIZE = 16;
  
  Vector2 pos_;
};

#endif
