#ifndef CLIENT_H_
# define CLIENT_H_

# include <string>
# include "AEntity.h"
# include "ISocket.h"

class ClientGame
{
public:
  ClientGame(int, int, const std::string &, ISocket *);
  ~ClientGame();
  int getIdPlayer() const;
  void setIdPlayer(int);
  int getIdClient() const;
  void setEntity(AEntity *);
  AEntity *getEntity() const;
  void setIdEntity(int);
  const std::string &getName() const;
  int getScore() const;
  int *getPScore();
  void setScore(int);
  ISocket *getSock() const;
  bool isReady() const;
  void ready(bool);

private:
  int idPlayer_;
  ISocket *sock_;
  std::string name_;
  int idClient_;
  bool isReady_;
  int score_;
  AEntity *entity_;
};

class ClientServer
{
public:
  ClientServer(int, const std::string &);
  ~ClientServer();
  const std::string &getRoom() const;
  const std::string &getName() const;
  int getIdClient() const;
  void setRoom(const std::string &);

private:
  int idClient_;
  std::string name_;
  std::string room_;
};

#endif
