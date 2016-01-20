#ifndef PACKET_BUILDER_H_
#define PACKET_BUILDER_H_

#include <map>
#include "IPacket.h"

class PacketBuilder
{
public:
  PacketBuilder();
  ~PacketBuilder();

  IPacket *build(char *, int);
private:
  typedef IPacket *(PacketBuilder::*memBuilder)(int, char *);

  IPacket *buildIntPacket(int, char *);
  IPacket *buildBytePacket(int, char *);
  IPacket *buildSimplePacket(int, char *);
  IPacket *buildStringPacket(int, char *);
  IPacket *buildReturnPacket(int, char *);
  IPacket *buildVector2Packet(int, char *);
  IPacket *buildVector3Packet(int, char *);
  IPacket *buildEntityCreatePacket(int, char *);
  IPacket *buildEntityUpdatePacket(int, char *);
  IPacket *buildRoomInfoPacket(int, char *);
  IPacket *buildGameStartPacket(int, char *);

  std::map<int, memBuilder> builder_;
};

#endif
