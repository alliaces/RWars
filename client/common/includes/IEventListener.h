#ifndef IEVENT_LISTENER_H_
#define IEVENT_LISTENER_H_

#include "Event.h"
#include "Packet.h"

class IEventListener
{
public:
  ~IEventListener() { }

  virtual int doEvent(Event::id, void *) = 0;
};

#endif
