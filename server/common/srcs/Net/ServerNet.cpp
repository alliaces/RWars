#include "ServerNet.h"

ServerNet::ServerNet(protocolId protocol, int port) : select_(*this, protocol, port)
{
  maxId_ = 0;
  select_.onClientRead = &ServerNet::clientRead;
  select_.onServerRead = &ServerNet::serverRead;
  select_.onClientWrite = &ServerNet::clientWrite;
}

ServerNet::~ServerNet()
{
  this->clearDatas();
}

void ServerNet::add(int clientId, ISocket *sock)
{
  select_.add(clientId, sock);
}

void ServerNet::remove(int clientId)
{
  select_.remove(clientId);
}

void ServerNet::send(IPacket *packet)
{
  if (packet)
  {
    select_.toWrite(packet->build(), packet->getSize());
    delete packet;
  }
}

void ServerNet::send(int clientId, IPacket *packet)
{
  if (packet)
  {
    select_.toWrite(clientId, packet->build(), packet->getSize());
    delete packet;
  }
}

bool ServerNet::update(double time)
{
  this->clearDatas();
  return (select_.doSelect(time));
}

ISocket *ServerNet::getClient(int clientId) const
{
  return (select_.getClient(clientId));
}

void ServerNet::clientRead(int clientId, ISocket *sock)
{
  int len;
  char *data = new char[SOCK_LEN];
  if ((len = sock->recv(data, SOCK_LEN)) > 0)
  {
    datas_[clientId].first = data;
    datas_[clientId].second = len;
  }
  else
  {
    delete[] data;
    datas_[clientId].first = nullptr;
    datas_[clientId].second = -1;
  }
}

void ServerNet::clientWrite(int clientId, ISocket *sock, char *data, int size)
{
  (void)clientId;
  if (select_.getProtocol() == protocolId::TCP)
  {
    this->sendData(sock, data, size);
  }
  else if (select_.getProtocol() == protocolId::UDP)
  {
    ISocket *server = select_.getSocket();
    server->setRecvAddr(sock->getRecvAddr());
    server->send(data, size);
  }
  delete[] data;
}

void ServerNet::serverRead(ISocket *sock)
{
  if (select_.getProtocol() == protocolId::TCP)
  {
    ISocket *nsock = sock->accept();
    select_.add(maxId_++, nsock);
  }
  else if (select_.getProtocol() == protocolId::UDP)
  {
    int len;
    int clientId;
    char *data = new char[SOCK_LEN];

    if ((len = sock->recv(data, SOCK_LEN)) > 0)
    {
      if ((clientId = select_.find(sock->getRecvAddr())) < 0) //If the client does not exists in the list of clients, add him !
      {
        clientId = maxId_;
        #ifdef _WIN32
          select_.add(clientId, new WSocket(protocolId::UDP, INVALID_SOCKET, sock->getRecvAddr()));
        #elif __linux__
          select_.add(clientId, new USocket(protocolId::UDP, -1, sock->getRecvAddr()));
        #endif
        ++maxId_;
      }
      datas_[clientId].first = data;
      datas_[clientId].second = len;
    }
  }
}

void ServerNet::clearDatas()
{
  for (auto i = datas_.begin(); i != datas_.end(); ++i)
  {
    if ((i->second).first)
    {
      delete[] (i->second).first;
    }
  }
  datas_.clear();
}

const ServerNet::dataList& ServerNet::getDatas() const
{
  return (datas_);
}

bool ServerNet::sendData(ISocket *sock, char *data, int size)
{
  int i = 0, j = 0;

  while (i < size)
  {
    if ((j = sock->send(data + i, size - i)) < 0)
      return (false);
    i += j;
  }
  return (true);
}
