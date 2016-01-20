#include "CNetManager.h"

CNetManager::CNetManager(IEventListener *listener, protocolId protocol) : net_(protocol)
{
  listener_ = listener;
  eventHandler_[Event::PACKET] = &CNetManager::eventPacket;
}

CNetManager::~CNetManager() { }

bool CNetManager::connect(const std::string& ip, int port)
{
  return (net_.connect(ip, port));
}

bool CNetManager::update()
{
  ClientNet::dataRecv data;

  if (!net_.update())
  {
    return (false);
  }
  data = net_.getData();
  if (data.first)
  {
    packetManager_.appendBinary(data.first, data.second, 0);
    if (!packetManager_.handle(0)) //If handle return false, the client is compromised
    {
      return (false);
    }
  }
  this->sendPacketsToListener();
  return (true);
}

void CNetManager::send(IPacket *packet)
{
  net_.send(packet);
}

void CNetManager::sendPacketsToListener()
{
  IPacket *packet = nullptr;

  while ((packet = packetManager_.pollPacket()))
  {
    if (listener_)
    {
      listener_->doEvent(Event::PACKET, packet);
    }
  }
}

int CNetManager::doEvent(Event::id id, void *param)
{
  if (param)
  {
    (this->*eventHandler_[id])(param);
  }
  return (0);
}

void CNetManager::eventPacket(void *data)
{
  IPacket *packet = (IPacket *)data;
  this->send(packet);
}
