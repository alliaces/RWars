#include "Vector3.h"

Vector3::Vector3(int x, int y, int z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3::Vector3(const Vector3& v)
{
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
}

Vector3::~Vector3() { }

Vector3& Vector3::operator=(const Vector3& v)
{
  if (&v == this)
    return (*this);
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  return (*this);
}
