#ifndef CLIENT_NET_H_
#define CLIENT_NET_H_

#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "ISocket.h"
#include "IPacket.h"

#ifdef _WIN32
  #include "WSocket.h"
#elif __linux__
  #include "USocket.h"
#endif

# define SOCK_LEN 1024

class ClientNet
{
public:
  typedef std::pair<char *, int> dataRecv;

  ClientNet(protocolId);
  ~ClientNet();

  bool connect(const std::string&, int);

  void send(IPacket *);
  bool update();

  const dataRecv& getData() const;
  void clearData();
  private:
  bool sendData(ISocket *, char *, int);
private:
  dataRecv data_;
  ISocket *sock_;
  std::queue<IPacket *> packets_;
  bool isConnected_;

  bool send();
  bool recv();
};

#endif
