#include "Vector2Packet.h"

Vector2Packet::Vector2Packet(int op, const Vector2& v) : APacket(op)
{
  pos_ = v;
  size_ = this->SIZE;
}

Vector2Packet::~Vector2Packet() { }

void Vector2Packet::setPosition(const Vector2& v)
{
  pos_ = v;
}

const Vector2& Vector2Packet::getPosition() const
{
  return (pos_);
}

char *Vector2Packet::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, &pos_.x, 4);
  std::memcpy(packet + 12, &pos_.y, 4);
  return (packet);
}
