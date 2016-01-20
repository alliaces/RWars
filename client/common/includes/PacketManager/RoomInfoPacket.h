#ifndef ROOM_INFO_PACKET_H_
#define ROOM_INFO_PACKET_H_

#include <string>
#include "APacket.h"

class RoomInfoPacket : public APacket
{
public:
  RoomInfoPacket(const std::string&, int, bool);
  ~RoomInfoPacket();

  void setRoom(const std::string&);
  void setNumberOfPlayers(int);
  void setAvailable(bool);

  const std::string& getRoom() const;
  int getNumberOfPlayers() const;
  bool isAvailable() const;

  char *build();
private:
  std::string room_;
  int numberOfPlayers_;
  bool available_;
};

#endif
