#ifndef		WAITSCENE_H_
# define	WAITSCENE_H_

#include <AirEngine.h>
#include <string>
#include "Ui.h"
#include "IUiListener.h"

class Ui;

class WaitScene : public AScene, public OnClickListener, public IUiListener
{
public:
  WaitScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes);
  ~WaitScene();
  void OnInit();
  void OnRender();
  void OnResize(Vector2u wsize);
  void OnClick(void *);
  void OnEvent(UiEvent event, void*);
  void initPlayerText();
private:
  Ui* ui_;
  AirWindow* window_;
  SceneMediator* scenes_;
  ResourceMediator *resourceMediator_;
  std::vector<AirText*> playersInRoom_;
  int nbPlayerInRoom;
  int timerNotify_;
  bool isNotifyDisplay_;
  AirText* textNotify_;
  AirButton* quitRoomButton_;
  AirButton* readyRoomButton_;
};

#endif
