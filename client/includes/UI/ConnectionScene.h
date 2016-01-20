#ifndef		CONNECTIONSCENE_H_
# define	CONNECTIONSCENE_H_

#include <AirEngine.h>
#include "Ui.h"
#include "IUiListener.h"
#include "UtilsSplit.h"
#ifdef _WIN32
#include "WindowsFileHandler.h"
#endif

#ifdef __linux__
#include "LinuxFileHandler.h"
#endif

class Ui;

class ConnectionScene : public AScene, public OnClickListener, public IUiListener
{
public:
  ConnectionScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes);
  ~ConnectionScene();
  void OnInit();
  void OnRender();
  void OnResize(Vector2u wsize);
  void OnClick(void *);
  void OnEvent(UiEvent event, void*);
  void rememberConnection();
  void readConnectionConfigs();
  void writeConnectionConfigs();
private:
  AFileHandler* fileHandler_;
  AirText* lblerror;
  Ui* ui_;
  SceneMediator* scenes_;
  ResourceMediator *resourceMediator_;
  AirWindow* window_;
  AirTextBox* ip_;
  AirTextBox* port_;
  AirText* rememberServerConnection_;
  AirCheckBox* rememberServer_;
};

#endif
