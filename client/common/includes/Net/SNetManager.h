#ifndef SNET_MANAGER_H_
#define SNET_MANAGER_H_

#include <map>

#include "IPacket.h"
#include "ServerNet.h"
#include "ByteArray.h"
#include "EventManager.h"
#include "PacketManager.h"
#include "IEventListener.h"

class SNetManager : public IEventListener
{
public:
  typedef void (SNetManager::*handler)(void *);

  SNetManager(IEventListener *, protocolId, int);
  ~SNetManager();

  bool update(double);

  void add(int, ISocket *);
  void remove(int);
  void send(IPacket *);
  void send(int, IPacket *);
  ISocket *getClient(int) const;

  int doEvent(Event::id, void *);
private:
  ServerNet net_;
  IEventListener *listener_;
  PacketManager packetManager_;

  std::map<Event::id, handler> eventHandler_;
  void eventPacket(void *);
protected:
  void sendPacketsToListener();
  void disconnectClient(int);
};

#endif
