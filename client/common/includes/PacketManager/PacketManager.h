#ifndef PACKET_MANAGER_H_
#define PACKET_MANAGER_H_

#include <queue>
#include <map>

#include "IPacket.h"
#include "ByteArray.h"
#include "PacketBuilder.h"

class PacketManager
{
public:
  PacketManager();
  ~PacketManager();

  void addPacket(IPacket *);
  void appendBinary(char *, int, int);
  bool handle(int);
  void clear(int);

  IPacket *pollPacket();
private:
  int handlePacket(int);

  PacketBuilder builder_;
  std::map<int, ByteArray> data_;
  std::queue<IPacket *> packets_;
};

#endif
