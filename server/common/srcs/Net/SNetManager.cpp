#include "SNetManager.h"

SNetManager::SNetManager(IEventListener *listener, protocolId protocol, int port) : net_(protocol, port)
{
  listener_ = listener;
  eventHandler_[Event::PACKET]     = &SNetManager::eventPacket;
}

SNetManager::~SNetManager() { }

bool SNetManager::update(double time)
{
  ServerNet::dataList datas;

  if (!net_.update(time))
    return (false);
  datas = net_.getDatas();
  for (auto i = datas.begin(); i != datas.end(); ++i)
  {
    if ((i->second).first && (i->second).second > 0) //If datas were recveived
    {
      packetManager_.appendBinary((i->second).first, (i->second).second, i->first);
      if (!packetManager_.handle(i->first)) //If handle return false, the client is compromised
      {
        this->disconnectClient(i->first);
      }
    }
    else //A client has disconnected
    {
      this->disconnectClient(i->first);
    }
  }
  this->sendPacketsToListener();
  return (true);
}

void SNetManager::add(int clientId, ISocket *sock)
{
  net_.add(clientId, sock);
}

void SNetManager::remove(int clientId)
{
  net_.remove(clientId);
}

void SNetManager::send(IPacket *packet)
{
  net_.send(packet);
}

void SNetManager::send(int clientId, IPacket *packet)
{
  net_.send(clientId, packet);
}

ISocket *SNetManager::getClient(int clientId) const
{
  return (net_.getClient(clientId));
}

void SNetManager::sendPacketsToListener()
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

void SNetManager::disconnectClient(int clientId)
{
  if (listener_)
  {
    listener_->doEvent(Event::CLIENT_DISCONNECT, new int(clientId));
  }
  packetManager_.clear(clientId);
  net_.remove(clientId);
}

int SNetManager::doEvent(Event::id id, void *param)
{
  if (param)
  {
    (this->*eventHandler_[id])(param);
  }
  return (0);
}

void SNetManager::eventPacket(void *data)
{
  IPacket *packet = (IPacket *)data;
  this->send(packet->getClientId(), packet);
}
