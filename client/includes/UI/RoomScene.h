#ifndef		ROOMSCENE_H_
# define	ROOMSCENE_H_

#include <AirEngine.h>
#include "Ui.h"
#include "IUiListener.h"

class Ui;

class RoomScene : public AScene, public OnClickListener, public IUiListener
{
public:
  RoomScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes);
  ~RoomScene();
  void OnInit();
  void OnRender();
  void OnResize(Vector2u wsize);
  void OnClick(void *);
  void OnEvent(UiEvent event, void*);
  void initRoomScreen();
  void initCreateRoomScreen();
  void removeCreateRoomScreen();
  void refreshRoomScreen();
  void addRoomScreen();
private:
  Ui* ui_;
  AirWindow* window_;
  SceneMediator* scenes_;
  ResourceMediator *resourceMediator_;
  std::vector<AirButton*> roomsButtons_;
  AirSprite* roomFrame_;
  AirSprite* roomCreationFrame_;
  AirTextBox *newRoomTitle_;
  AirText *roomCreation_;
  int timerNotify_;
  bool isNotifyDisplay_;
  AirText *textNotify_;
  AirButton* refreshButton_;
  AirButton* createRoomButton_;
  AirButton* okButton_;
  AirButton* cancelButton_;
  int posLastButtonRoom_;
  int maxPosLastButtonRoom_;
  int posPageRoom_;
  int nbPageRoom_;
  int frameUpPress_;
  int frameDownPress_;
};

#endif
