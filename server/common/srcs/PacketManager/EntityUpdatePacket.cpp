#include "EntityUpdatePacket.h"

EntityUpdatePacket::EntityUpdatePacket(int id, const Vector3& pos, int sprite) : APacket(Packet::ENTITY_UPDATE)
{
  size_ = this->SIZE;
  this->setEntityId(id);
  this->setPosition(pos);
  this->setSpriteId(sprite);
}

EntityUpdatePacket::~EntityUpdatePacket() { }

void EntityUpdatePacket::setEntityId(int id)
{
  entityId_ = id;
}

void EntityUpdatePacket::setPosition(const Vector3& pos)
{
  pos_ = pos;
}

void EntityUpdatePacket::setSpriteId(int id)
{
  spriteId_ = id;
}

int EntityUpdatePacket::getEntityId() const
{
  return (entityId_);
}

const Vector3& EntityUpdatePacket::getPosition() const
{
  return (pos_);
}

int EntityUpdatePacket::getSpriteId() const
{
  return (spriteId_);
}

char *EntityUpdatePacket::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, &entityId_, 4);
  std::memcpy(packet + 12, &pos_.x, 4);
  std::memcpy(packet + 16, &pos_.y, 4);
  std::memcpy(packet + 20, &pos_.z, 4);
  std::memcpy(packet + 24, &spriteId_, 4);
  return (packet);
}
