#ifndef GAME_PACKET_H_
#define GAME_PACKET_H_

#include <string>
#include "APacket.h"

class GameStartPacket : public APacket
{
public:
  GameStartPacket(const std::string&, int);
  ~GameStartPacket();

  void setIp(const std::string&);
  void setPort(int);

  const std::string& getIp() const;
  int getPort() const;

  char *build();
private:
  std::string ip_;
  int port_;
};

#endif
