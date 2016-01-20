#ifndef		UI_H_
# define	UI_H_

#include <AirEngine.h>
#include "ResourceMediator.h"
#include "SceneMediator.h"
#include "IUiListener.h"
#include "ARunnableThread.h"
#include "IEventListener.h"

class SceneMediator;

class Ui : public IUiListener, public ARunnableThread, public IEventListener
{
 public:
  Ui();
  ~Ui();
  void setUDPListener(IEventListener *lis);
  void setTCPListener(IEventListener *lis);
  void *run(void *);
  void OnEvent(UiEvent event, void*);
  int doEvent(Event::id, void*);
 private:
  IEventListener *UDPlis;
  IEventListener *TCPlis;
  AirWindow *window_;
  SceneMediator *sceenMediator_;
  ResourceMediator *resourceMediator_;
};

#endif
