#include "Vector2.h"

Vector2::Vector2(int x, int y)
{
  this->x = x;
  this->y = y;
}

Vector2::Vector2(const Vector2& v)
{
  this->x = v.x;
  this->y = v.y;
}

Vector2::~Vector2() { }

Vector2& Vector2::operator=(const Vector2& v)
{
  if (&v == this)
    return (*this);
  this->x = v.x;
  this->y = v.y;
  return (*this);
}
