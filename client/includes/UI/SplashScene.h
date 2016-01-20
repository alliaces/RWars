#ifndef		SPLASHSCENE_H_
# define	SPLASHSCENE_H_

#include <AirEngine.h>
#include "Ui.h"
#include "IUiListener.h"

class Ui;
class SceneMediator;

class SplashScene : public AScene, IUiListener
{
public:
  SplashScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes);
	~SplashScene();
    void OnInit();
    void OnRender();
    void OnResize(Vector2u wsize);
    void OnEvent(UiEvent event, void*);
private:
    AirWindow* window_;
    SceneMediator* scenes_;
    AirText *press;
    unsigned int time_;
    bool isPressVisible;
};

#endif
