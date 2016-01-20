#ifndef CNET_MANAGER_H_
#define CNET_MANAGER_H_

#include <map>

#include "IPacket.h"
#include "ClientNet.h"
#include "ByteArray.h"
#include "EventManager.h"
#include "PacketManager.h"
#include "IEventListener.h"

class CNetManager : public IEventListener
{
public:
  typedef void (CNetManager::*handler)(void *);

  CNetManager(IEventListener *, protocolId);
  ~CNetManager();

  bool connect(const std::string&, int);
  bool update();

  void send(IPacket *);

  int doEvent(Event::id, void *);
private:
  ClientNet net_;
  IEventListener *listener_;
  PacketManager packetManager_;

  std::map<Event::id, handler> eventHandler_;
  void eventPacket(void *);
protected:
  void sendPacketsToListener();
};

#endif
