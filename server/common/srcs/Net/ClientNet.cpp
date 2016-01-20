#include "ClientNet.h"

ClientNet::ClientNet(protocolId protocol)
{
  sock_ = nullptr;
#ifdef _WIN32
  sock_ = new WSocket(protocol);
#elif __linux__
  sock_ = new USocket(protocol);
#endif
  if (!sock_)
  {
    throw std::runtime_error("Cannot run ClientNet: Platerform not supported");
  }
  isConnected_ = false;
}

ClientNet::~ClientNet()
{
  while (!packets_.empty())
  {
    delete packets_.front();
    packets_.pop();
  }
  this->clearData();
}

bool ClientNet::connect(const std::string& addr, int port)
{
  if (!sock_->connect(addr, port))
  {
    return (false);
  }
  isConnected_ = true;
  return (true);
}

void ClientNet::send(IPacket *packet)
{
  if (packet)
  {
    packets_.push(packet);
  }
}

bool ClientNet::send()
{
  char *data;
  bool e = true;
  IPacket *packet;

  while (!packets_.empty())
  {
    packet = packets_.front();
    if (e)
    {
      data = packet->build();
      e = sendData(sock_, data, packet->getSize());
      delete[] data;
    }
    packets_.pop();
    delete packet;
  }
  return (e);
}

bool ClientNet::recv()
{
  int len;
  char *data = new char[SOCK_LEN];

  sock_->setBlocking(false);
  if ((len = sock_->recv(data, SOCK_LEN)) < 0)
  {
    if (sock_->getLastError() == SOCKET_WBLOCK)
    {
      delete[] data;
      return (true);
    }
    else //Server was closed !
    {
      delete[] data;
      return (false);
    }
  }
  data_.first = data;
  data_.second = len;
  return (true);
}

bool ClientNet::update()
{
  this->clearData();
  if (isConnected_)
  {
    this->recv();
    return (this->send());
  }
  return (true);
}

void ClientNet::clearData()
{
  if (data_.first)
  {
    delete[] data_.first;
  }
  data_.first = nullptr;
  data_.second = 0;
}

const ClientNet::dataRecv& ClientNet::getData() const
{
  return (data_);
}

bool ClientNet::sendData(ISocket *sock, char *data, int size)
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
