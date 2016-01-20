#include "EntityCreatePacket.h"

EntityCreatePacket::EntityCreatePacket(int id, const Vector3& pos, const Vector2& scale, int sprite, const std::string& name) : APacket(Packet::ENTITY_CREATE)
{
  size_ = this->SIZE + 1;
  this->setEntityId(id);
  this->setPosition(pos);
  this->setScale(scale);
  this->setSpriteId(sprite);
  this->setName(name);
}

EntityCreatePacket::~EntityCreatePacket() { }

void EntityCreatePacket::setEntityId(int id)
{
  entityId_ = id;
}

void EntityCreatePacket::setName(const std::string& name)
{
  name_ = name;
  size_ = this->SIZE + name_.length() + 1;
}

void EntityCreatePacket::setPosition(const Vector3& pos)
{
  pos_ = pos;
}

void EntityCreatePacket::setScale(const Vector2& scale)
{
  scale_ = scale;
}

void EntityCreatePacket::setSpriteId(int id)
{
  spriteId_ = id;
}

int EntityCreatePacket::getEntityId() const
{
  return (entityId_);
}

const std::string& EntityCreatePacket::getName() const
{
  return (name_);
}

const Vector3& EntityCreatePacket::getPosition() const
{
  return (pos_);
}

const Vector2& EntityCreatePacket::getScale() const
{
  return (scale_);
}

int EntityCreatePacket::getSpriteId() const
{
  return (spriteId_);
}

char *EntityCreatePacket::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, &entityId_, 4);
  std::memcpy(packet + 12, &pos_.x, 4);
  std::memcpy(packet + 16, &pos_.y, 4);
  std::memcpy(packet + 20, &pos_.z, 4);
  std::memcpy(packet + 24, &scale_.x, 4);
  std::memcpy(packet + 28, &scale_.y, 4);
  std::memcpy(packet + 32, &spriteId_, 4);
  std::memcpy(packet + 36, name_.c_str(), name_.length() + 1);
  return (packet);
}
