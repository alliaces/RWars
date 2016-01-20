#ifndef         NETWORK_H_
# define        NETWORK_H_

#include "CNetManager.h"
#include "IEventListener.h"
#include "ARunnableThread.h"

class Network : public ARunnableThread
{
 public:
  Network(IEventListener *lis);
  ~Network();
  void *run(void *);
  IEventListener* getTCPListener();
  IEventListener* getUDPListener();
 private:
  CNetManager *netUDP;
  CNetManager *netTCP;
  IEventListener *lis;
};

#endif
