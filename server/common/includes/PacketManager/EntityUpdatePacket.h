#ifndef ENTITY_UPDATE_PACKET_H_
#define ENTITY_UPDATE_PACKET_H_

#include <string>
#include "APacket.h"
#include "Vector3.h"

class EntityUpdatePacket : public APacket
{
public:
  EntityUpdatePacket(int, const Vector3&, int);
  ~EntityUpdatePacket();

  void setEntityId(int);
  void setPosition(const Vector3&);
  void setSpriteId(int);

  int getEntityId() const;
  const Vector3& getPosition() const;
  int getSpriteId() const;

  char *build();
private:
  const int SIZE = 28;

  int entityId_;
  Vector3 pos_;
  int spriteId_;
};

#endif
