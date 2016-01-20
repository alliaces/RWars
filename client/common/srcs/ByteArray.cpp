#include "ByteArray.h"

ByteArray::ByteArray(char *bytes, int size)
{
  size_ = 0;
  bytes_ = nullptr;
  this->set(bytes, size);
}

ByteArray::~ByteArray()
{
  this->clear();
}

void ByteArray::clear()
{
  if (bytes_)
  {
    delete[] bytes_;
  }
  bytes_ = nullptr;
  size_ = 0;
}

void ByteArray::set(char *bytes, int size)
{
  this->clear();
  if (bytes)
  {
    size_ = size;
    bytes_ = new char[size_];
    std::memcpy(bytes_, bytes, size_);
    return;
  }
}

void ByteArray::append(char *bytes, int size)
{
  if (!bytes)
    return;
  if (!bytes_)
  {
    this->set(bytes, size);
    return;
  }
  char *tmp = new char[size_ + size];
  std::memcpy(tmp, bytes_, size_);
  std::memcpy(tmp + size_, bytes, size);
  delete[] bytes_;
  size_ += size;
  bytes_ = tmp;
}

void ByteArray::append(int n, int size)
{
  this->append((char *)&n, size);
}

bool ByteArray::erase(int from, int size)
{
  if (size <= 0)
    return (true);
  if (from < 0 || from + size > size_)
    return (false);
  if (size == size_)
  {
    this->clear();
    return (true);
  }
  char *tmp = new char[size_ - size];
  std::memcpy(tmp, bytes_, from);
  std::memcpy(tmp + from, bytes_ + from + size, size_ - from - size);
  delete[] bytes_;
  bytes_ = tmp;
  size_ -= size;
  return (true);
}

int ByteArray::getSize() const
{
  return (size_);
}

char *ByteArray::getBytes() const
{
  return (bytes_);
}
