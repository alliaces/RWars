#ifndef VECTOR3_H_
#define VECTOR3_H_

class Vector3
{
public:
  Vector3(int x = 0, int y = 0, int z = 0);
  Vector3(const Vector3&);
  ~Vector3();

  Vector3& operator=(const Vector3&);

  int x;
  int y;
  int z;
};

#endif
