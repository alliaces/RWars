#include <chrono>
#include <thread>
#include "Network.h"
#ifdef _WIN32
	#include "windows.h"
#endif
Network::Network(IEventListener *lis)
{
  this->lis = lis;
  netTCP = new CNetManager(lis, protocolId::TCP);
  netUDP = new CNetManager(lis, protocolId::UDP);
}

Network::~Network()
{
  
}

void *Network::run(void *)
{
  while (1)
    {
      if (!this->netTCP->update() && lis)
	dynamic_cast<IEventListener*>(lis)->doEvent(Event::CLIENT_DISCONNECT,NULL);
      this->netUDP->update();
#ifndef _WIN32
      usleep(100);
#else
	
	#endif
    }
  return (NULL);
}

IEventListener* Network::getTCPListener()
{
  return (netTCP);
}

IEventListener* Network::getUDPListener()
{
  return (netUDP);
}
