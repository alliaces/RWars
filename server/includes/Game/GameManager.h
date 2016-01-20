#ifndef GAMEMANAGER_H_
# define GAMEMANAGER_H_

# include <map>
# include <string>
# include <iostream>

#ifdef _WIN32
  # include <windows.h>
#else
  # include <signal.h>
#endif
# include "Game.h"
# include "ThreadsManager.h"
# include "StringPacket.h"
# include "Client.h"
# include "ReturnPacket.h"
# include "Packet.h"
# include "RoomInfoPacket.h"
# include "BytePacket.h"
# include "GameStartPacket.h"
# include "GameBuilder.h"
# include "EntityManager.h"

class GameManager : public IEventListener
{
public:
  GameManager();
  ~GameManager();
  void start(SNetManager *, int, const std::vector<std::string> &);
  int doEvent(Event::id, void *);

private:
  void checkNewPlugins();
  void checkEmptyRoom();
  void checkEndedGames();
  void createRoom(const std::string &, int);
  void joinRoom(const std::string &, int);
  void getInfoRooms(int) const;
  void sendJoinRoom(const std::string &, int);
  void sendRoomJoin(const std::string &, int);
  void sendLeaveRoom(const std::string &, int);
  void beginGame(const std::string &);
  void handleCreate(void *);
  void handleJoin(void *);
  void handleAuth(void *);
  void handleReady(void *);
  void handleLeave(void *);
  void handleDisconnect(void *);
  void handleInfo(void *);

  SNetManager *net_;
  GameBuilder *builder_;
  EntityManager *eManager_;
  ThreadsManager thread_;
  int timerPlugin_;
  std::map<int, ClientServer *> clients_;
  std::map<std::string, Game *> rooms_;
  std::map<Packet::id, void (GameManager::*)(void *)> events_;
};

#endif
