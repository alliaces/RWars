#ifndef VECTOR2_H_
#define VECTOR2_H_

class Vector2
{
public:
  Vector2(int x = 0, int y = 0);
  Vector2(const Vector2&);
  ~Vector2();

  Vector2& operator=(const Vector2&);

  int x;
  int y;
};

#endif
