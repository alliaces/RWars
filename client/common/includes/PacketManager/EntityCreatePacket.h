#ifndef ENTITY_CREATE_PACKET_H_
#define ENTITY_CREATE_PACKET_H_

#include <string>
#include "APacket.h"
#include "Vector3.h"
#include "Vector2.h"

class EntityCreatePacket : public APacket
{
public:
  EntityCreatePacket(int, const Vector3&, const Vector2&, int, const std::string& name = "");
  ~EntityCreatePacket();

  void setEntityId(int);
  void setPosition(const Vector3&);
  void setScale(const Vector2&);
  void setSpriteId(int);
  void setName(const std::string&);

  int getEntityId() const;
  const Vector3& getPosition() const;
  const Vector2& getScale() const;
  int getSpriteId() const;
  const std::string& getName() const;

  char *build();
private:
  const int SIZE = 36;

  int entityId_;
  std::string name_;
  Vector3 pos_;
  Vector2 scale_;
  int spriteId_;
};

#endif
