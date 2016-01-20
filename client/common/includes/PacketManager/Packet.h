#ifndef PACKET_H_
#define PACKET_H_

namespace Packet
{
  enum id
  {
    AUTH            = 0x00,
    ROOM_JOIN       = 0x02,
    ROOM_CREATE     = 0x03,
    READY           = 0x05,
    ROOM_LEAVE      = 0x30,
    ROOM_REFRESH    = 0x33,
    RETURN          = 0x04,
    ROOM_INFO       = 0x01,
    HAS_JOINED      = 0x06,
    HAS_LEFT        = 0x07,
    START_GAME      = 0x08,
    UPDATE_POS      = 0x23,
    PLAYER_SHOT     = 0x24,
    PLAYER_SCORE    = 0x28,
    ROOM_BACK       = 0x31,
    ENTITY_CREATE   = 0x20,
    ENTITY_UPDATE   = 0x21,
    ENTITY_DESTROY  = 0x22,
    ENTITY_LIFE     = 0x25,
    ENTITY_POINT    = 0x26,
    SPECTATOR       = 0x27,
    FINAL_SCORE     = 0x29,
    SCROLLING       = 0x32
  };
}

#endif
