#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <map>
#include <iostream>

#include "Event.h"
#include "Packet.h"
#include "IPacket.h"
#include "IEventListener.h"

class EventManager
{
public:
  EventManager(IEventListener *);
  ~EventManager();

  void send(IPacket *);
  void send(Event::id, void *);

  Event::id getIdFromPacket(Packet::id) const;
private:
  IEventListener *listener_;
  std::map<Packet::id, Event::id> packetToEvent_;
};

#endif
