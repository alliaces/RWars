#ifndef SELECT_H_
#define SELECT_H_

#include <map>
#include <vector>
#include <utility>
#include <sstream>
#include <stdexcept>

#include "Utils.h"
#include "ISocket.h"

#ifdef _WIN32
  #include "WSocket.h"
#elif __linux__
  #include "USocket.h"
#endif

template <class T>
class Select
{
public:
  typedef void (T::*serverReadFunc)(ISocket *);
  typedef void (T::*clientReadFunc)(int, ISocket *);
  typedef void (T::*clientWriteFunc)(int, ISocket *, char *, int);

  Select(T& instance, protocolId protocol, int port) : instance_(instance)
  {
    sock_ = nullptr;
  #ifdef _WIN32
    sock_ = new WSocket(protocol);
  #elif __linux__
    sock_ = new USocket(protocol);
  #endif
    if (!sock_)
    {
      throw std::runtime_error("Cannot run Select: Platerform not supported");
    }
    if (!sock_->bind(port))
    {
      std::stringstream ss;
      ss << "Cannot run Select - Error " << sock_->getLastError();
      throw std::runtime_error(ss.str());
    }
    if (protocol == protocolId::UDP)
    {
      sock_->setBlocking(false);
    }
    maxClient_ = sock_->getId();
  }

  ~Select()
  {
    delete sock_;
    for (auto it = clients_.begin(); it != clients_.end(); ++it)
      delete it->second;
  }

  void add(int clientId, ISocket *sock)
  {
    if (sock)
    {
      clients_[clientId] = sock;
      if (sock->getId() > maxClient_)
        maxClient_ = sock->getId();
    }
  }

  void remove(int clientId)
  {
    write_[clientId].clear();
    delete clients_[clientId];
    clients_.erase(clientId);
    maxClient_ = this->lowestClientId();
  }

  bool doSelect(double time)
  {
    struct timeval timeout;

    this->init();
    Utils::doubleToTimeval(time, &timeout);
    if (::select(maxClient_ + 1, &fs_[0], &fs_[1], NULL, &timeout) < 0)
      return (false);
    this->accept();
    this->write();
    this->read();
    return (true);
  }

  void toWrite(int clientId, char *data, int size)
  {
    if (this->exists(clientId))
    {
      write_[clientId].push_back(std::make_pair(data, size));
    }
  }

  void toWrite(char *data, int size)
  {
    for (auto i = clients_.begin(); i != clients_.end(); ++i)
      this->toWrite(i->first, data, size);
  }

  ISocket *getClient(int clientId) const
  {
    if (this->exists(clientId))
      return (clients_.at(clientId));
    return (nullptr);
  }

  bool exists(int clientId) const
  {
    if (clients_.find(clientId) != clients_.end())
      return (true);
    return (false);
  }

  int find(const void *addr)
  {
    for (auto i = clients_.begin(); i != clients_.end(); ++i)
    {
      if (Utils::contentEquals((i->second)->getRecvAddr(), addr, SOCK_ADDR_SIZE))
        return (i->first);
    }
    return (-1);
  }

  protocolId getProtocol() const
  {
    return (sock_->getProtocol());
  }

  ISocket *getSocket() const
  {
    return (sock_);
  }

  serverReadFunc onServerRead;
  clientReadFunc onClientRead;
  clientWriteFunc onClientWrite;
private:
  typedef std::map<int, ISocket *> clientList;
  typedef std::map<int, std::vector<std::pair<char *, int> > > dataToWrite;

  fd_set fs_[2];
  unsigned int maxClient_;
  T& instance_;

  void init()
  {
    FD_ZERO(&fs_[0]);
    FD_ZERO(&fs_[1]);
    FD_SET(sock_->getId(), &fs_[0]);
    if (this->getProtocol() == protocolId::UDP)
    {
      for (auto it = write_.begin(); it != write_.end(); ++it)
      {
        if (!(it->second).empty())
        {
          FD_SET(sock_->getId(), &fs_[1]);
          break;
        }
      }
    }
    if (this->getProtocol() == protocolId::TCP)
    {
      for (auto it = clients_.begin(); it != clients_.end(); ++it)
      {
        FD_SET((it->second)->getId(), &fs_[0]);
      }
      for (auto it = write_.begin(); it != write_.end(); ++it)
      {
        if (!(it->second).empty())
          FD_SET(clients_[it->first]->getId(), &fs_[1]);
      }
    }
  }

  void accept()
  {
    if (FD_ISSET(sock_->getId(), &fs_[0]))
    {
      (instance_.*onServerRead)(sock_);
    }
  }

  void read()
  {
    clientList::iterator tmp;
    for (auto it = clients_.begin(); it != clients_.end();)
    {
      if ((it->second)->isConnected() && FD_ISSET((it->second)->getId(), &fs_[0]))
      {
        tmp = it++;
        (instance_.*onClientRead)(tmp->first, tmp->second);
        continue;
      }
      ++it;
    }
  }

  void write()
  {
    for (auto i = write_.begin(); i != write_.end(); ++i)
    {
      for (auto data = i->second.begin(); data != i->second.end(); ++data)
      {
        if (this->exists(i->first))
        {
          (instance_.*onClientWrite)(i->first, clients_[i->first], data->first, data->second);
        }
      }
      write_[i->first].clear();
    }
  }
protected:
  ISocket *sock_;
  clientList clients_;
  dataToWrite write_;

  int lowestClientId()
  {
    unsigned int max = sock_->getId();
    for (auto client = clients_.begin(); client != clients_.end(); ++client)
    {
      if ((client->second)->isConnected())
      {
        if ((client->second)->getId() > max)
          max = (client->second)->getId();
      }
    }
    return (max);
  }
};

#endif
