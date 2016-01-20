#include "PacketBuilder.h"

#include "IntPacket.h"
#include "BytePacket.h"
#include "ReturnPacket.h"
#include "SimplePacket.h"
#include "StringPacket.h"
#include "Vector2Packet.h"
#include "Vector3Packet.h"
#include "RoomInfoPacket.h"
#include "GameStartPacket.h"
#include "EntityCreatePacket.h"
#include "EntityUpdatePacket.h"

PacketBuilder::PacketBuilder()
{
  builder_[Packet::AUTH]            = &PacketBuilder::buildStringPacket;
  builder_[Packet::ROOM_JOIN]       = &PacketBuilder::buildStringPacket;
  builder_[Packet::ROOM_CREATE]     = &PacketBuilder::buildStringPacket;
  builder_[Packet::READY]           = &PacketBuilder::buildBytePacket;
  builder_[Packet::ROOM_LEAVE]      = &PacketBuilder::buildSimplePacket;
  builder_[Packet::ROOM_REFRESH]    = &PacketBuilder::buildSimplePacket;
  builder_[Packet::RETURN]          = &PacketBuilder::buildReturnPacket;
  builder_[Packet::ROOM_INFO]       = &PacketBuilder::buildRoomInfoPacket;
  builder_[Packet::HAS_JOINED]      = &PacketBuilder::buildStringPacket;
  builder_[Packet::HAS_LEFT]        = &PacketBuilder::buildStringPacket;
  builder_[Packet::START_GAME]      = &PacketBuilder::buildGameStartPacket;
  builder_[Packet::UPDATE_POS]      = &PacketBuilder::buildVector3Packet;
  builder_[Packet::PLAYER_SHOT]     = &PacketBuilder::buildSimplePacket;
  builder_[Packet::PLAYER_SCORE]    = &PacketBuilder::buildSimplePacket;
  builder_[Packet::ROOM_BACK]       = &PacketBuilder::buildSimplePacket;
  builder_[Packet::ENTITY_CREATE]   = &PacketBuilder::buildEntityCreatePacket;
  builder_[Packet::ENTITY_UPDATE]   = &PacketBuilder::buildEntityUpdatePacket;
  builder_[Packet::ENTITY_DESTROY]  = &PacketBuilder::buildIntPacket;
  builder_[Packet::ENTITY_LIFE]     = &PacketBuilder::buildVector2Packet;
  builder_[Packet::ENTITY_POINT]    = &PacketBuilder::buildVector2Packet;
  builder_[Packet::SPECTATOR]       = &PacketBuilder::buildSimplePacket;
  builder_[Packet::FINAL_SCORE]     = &PacketBuilder::buildVector2Packet;
  builder_[Packet::SCROLLING]       = &PacketBuilder::buildVector2Packet;
}

PacketBuilder::~PacketBuilder() { }

IPacket *PacketBuilder::build(char *data, int clientId)
{
  int opcode = *(int *)(data + 4);

  if (builder_.find(opcode) != builder_.end())
  {
    IPacket *packet;
    if ((packet = (this->*builder_[opcode])(opcode, data + HEADER_SIZE)) == nullptr)
      return (nullptr);
    packet->setClientId(clientId);
    return (packet);
  }
  return (nullptr);
}

IPacket *PacketBuilder::buildIntPacket(int opcode, char *data)
{
  return (new IntPacket(opcode, *(int *)data));
}

IPacket *PacketBuilder::buildBytePacket(int opcode, char *data)
{
  return (new BytePacket(opcode, *data));
}

IPacket *PacketBuilder::buildSimplePacket(int opcode, char *data)
{
  (void)data;
  return (new SimplePacket(opcode));
}

IPacket *PacketBuilder::buildStringPacket(int opcode, char *data)
{
  return (new StringPacket(opcode, data));
}

IPacket *PacketBuilder::buildReturnPacket(int opcode, char *data)
{
  (void)opcode;
  return (new ReturnPacket(*(int *)data, data + 4));
}

IPacket *PacketBuilder::buildVector2Packet(int opcode, char *data)
{
  return (new Vector2Packet(opcode, Vector2(*(int *)data, *(int *)(data + 4))));
}

IPacket *PacketBuilder::buildVector3Packet(int opcode, char *data)
{
  return (new Vector3Packet(opcode, Vector3(*(int *)data, *(int *)(data + 4), *(int *)(data + 8))));
}

IPacket *PacketBuilder::buildEntityCreatePacket(int opcode, char *data)
{
  (void)opcode;
  return (new EntityCreatePacket(*(int *)data, Vector3(*(int *)(data + 4), *(int *)(data + 8), *(int *)(data + 12)), Vector2(*(int *)(data + 16), *(int *)(data + 20)), *(int *)(data + 24), data + 28));
}

IPacket *PacketBuilder::buildEntityUpdatePacket(int opcode, char *data)
{
  (void)opcode;
  return (new EntityUpdatePacket(*(int *)data, Vector3(*(int *)(data + 4), *(int *)(data + 8), *(int *)(data + 12)), *(int *)(data + 16)));
}

IPacket *PacketBuilder::buildRoomInfoPacket(int opcode, char *data)
{
  (void)opcode;
  int i = std::strlen(data) + 1;
  return (new RoomInfoPacket(data, *(int *)(data + i), *(data + i + 4)));
}

IPacket *PacketBuilder::buildGameStartPacket(int opcode, char *data)
{
  (void)opcode;
  int i = std::strlen(data) + 1;
  return (new GameStartPacket(data, *(int *)(data + i)));
}
