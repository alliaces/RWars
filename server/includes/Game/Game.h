#ifndef GAME_H_
# define GAME_H_

# include <string>
# include <cstdlib>
# include <algorithm>
# include <chrono>
# include <thread>
# ifdef _WIN32
#  include <windows.h>
#  include "WinLoad.h"
#  define LOADER WLoad<AEntity> *
# elif __linux__
#  include "UnixLoad.h"
#  define LOADER ULoad<AEntity> *
# endif

# include "AEntity.h"
# include "ITick.h"
# include "Client.h"
# include "IEventListener.h"
# include "SNetManager.h"
# include "EntityContainer.h"
# include "Vector2Packet.h"
# include "Vector3Packet.h"
# include "SimplePacket.h"
# include "EntityCreatePacket.h"
# include "EntityUpdatePacket.h"
# include "StringPacket.h"
# include "IntPacket.h"
# include "ThreadsManager.h"
# include "Map.h"

class Game : public IEventListener
{
public:
  Game(const std::string &, const std::string &, int, EntityContainer *);
  ~Game();
  int getNbClients() const;
  int getNbClientsReady() const;
  int getIdClient(int) const;
  const std::string &getIp() const;
  int getPort() const;
  const std::string &getName() const;
  bool isPlaying() const;
  bool isFinished() const;
  void join(int, const std::string &, ISocket *);
  void leave(int);
  void leave(const std::string &);
  void ready(int, bool);
  void initGame();
  void update();
  static void *startGame(void *);
  int doEvent(Event::id, void *);

private:
  void handlePos(void *);
  void handleShoot(void *);
  void handleScore(void *);
  void handleLobby(void *);
  void handleDisconnect(void *);
  void handleAuth(void *);
  void handleCreate(void *);
  void movePlayer(int, int);
  void sendUpdateEntity(AEntity *);
  void shootPlayer(int);
  void shootMonster(AMonster *);
  void sendCreateEntity(AEntity *, const std::string &);
  void sendDestroyEntity(int);
  void checkMap();
  void createMonster();
  void checkMonster();
  void checkPlayer();
  void checkCollisions();
  void checkExplosion();
  void createBlock();
  void checkBlock();
  void checkCreate();
  void collisionShot(AEntity *, AEntity *);
  void collisionExplosion(AEntity *, AEntity *);
  void collisionBlock(AEntity *, AEntity *);
  void collisionBonus(AEntity *, AEntity *);
  void collisionPlayer(AEntity *, AEntity *);
  void collisionMonster(AEntity *, AEntity *);
  void sendFinalScore();
  void spawnBonus(AEntity *);
  void theEnd();
  void endGame();
  const Vector2 findClientEntity(AEntity *);
  AEntity *findEntityId(int);
  void setPlayerScore(int, int);

  SNetManager *net_;
  EntityContainer *container_;
  std::map<int, ClientGame *> clients_;
  Map map_;
  std::string name_;
  std::map<Packet::id, void (Game::*)(void *)> events_;
  std::map<std::string, void (Game::*)(AEntity *, AEntity *)> collisions_;
  bool game_;
  bool isFinished_;
  std::string ip_;
  int port_;
  int currentId_;
  int currentIdClient_;
  int nbMonsters_;
  int timerMonster_;
  int timerBlock_;
};

#endif
