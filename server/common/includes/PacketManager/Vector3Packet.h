#ifndef VECTOR3_PACKET_H_
#define VECTOR3_PACKET_H_

#include <string>
#include "APacket.h"
#include "Vector3.h"

class Vector3Packet : public APacket
{
public:
  Vector3Packet(int, const Vector3&);
  ~Vector3Packet();

  void setPosition(const Vector3&);
  const Vector3& getPosition() const;

  char *build();
private:
  const int SIZE = 20;

  Vector3 pos_;
};

#endif
