#ifndef SERVER_NET_H_
#define SERVER_NET_H_

#include "ISocket.h"
#include "IPacket.h"
#include "Select.h"

# define SOCK_LEN 1024

class ServerNet
{
public:
  typedef std::map<int, std::pair<char *, int> > dataList;

  ServerNet(protocolId, int);
  ~ServerNet();

  void add(int, ISocket *);
  void remove(int);
  void send(IPacket *);
  void send(int, IPacket *);
  bool update(double);
  ISocket *getClient(int) const;

  void clientRead(int, ISocket *);
  void clientWrite(int, ISocket *, char *, int);
  void serverRead(ISocket *);

  const dataList& getDatas() const;
  void clearDatas();
private:
  bool sendData(ISocket *, char *, int);

  int maxId_;
  Select<ServerNet> select_;
  dataList datas_;
};

#endif
