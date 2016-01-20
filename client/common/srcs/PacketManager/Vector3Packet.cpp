#include "Vector3Packet.h"

Vector3Packet::Vector3Packet(int op, const Vector3& v) : APacket(op)
{
  pos_ = v;
  size_ = this->SIZE;
}

Vector3Packet::~Vector3Packet() { }

void Vector3Packet::setPosition(const Vector3& v)
{
  pos_ = v;
}

const Vector3& Vector3Packet::getPosition() const
{
  return (pos_);
}

char *Vector3Packet::build()
{
  char *packet = new char[size_];
  std::memcpy(packet, &size_, 4);
  std::memcpy(packet + 4, &opcode_, 4);
  std::memcpy(packet + 8, &pos_.x, 4);
  std::memcpy(packet + 12, &pos_.y, 4);
  std::memcpy(packet + 16, &pos_.z, 4);
  return (packet);
}
