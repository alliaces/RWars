#ifndef BYTE_ARRAY_H_
#define BYTE_ARRAY_H_

#include <cstring>

class ByteArray
{
public:
  ByteArray(char *bytes = nullptr, int size = 0);
  ~ByteArray();

  void clear();
  void set(char *, int);
  void append(char *, int);
  void append(int, int);
  bool erase(int, int);

  int getSize() const;
  char *getBytes() const;
private:
  char *bytes_;
  int size_;
};

#endif
