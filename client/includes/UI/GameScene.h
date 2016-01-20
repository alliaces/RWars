#ifndef		GAMESCENE_H_
# define	GAMESCENE_H_

#include <AirEngine.h>
#include "Player.h"
#include "Entity.h"
#include "Ui.h"
#include "IUiListener.h"
#include <thread>

class Ui;

class GameScene : public AScene, public OnClickListener, public IUiListener
{
public:
  GameScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes);
  ~GameScene();
  void OnInit();
  void OnRender();
  void OnResize(Vector2u wsize);
  void OnClick(void *);
  void OnEvent(UiEvent event, void*);
private:
  bool hasLife;
  int life;
  int maxLife;
  bool isPress_;
  bool isDoublePress_;
  bool isShot_;
  std::vector<Player*> players_;
  std::vector<Entity*> entitys_;
  void CreateEntity(void* data);
  void UpdateEntity(void* data);
  void DestroyEntity(void* data);
  void SendUp();
  ResourceMediator *res_;
  Ui* ui_;
  AirWindow* window_;
  SceneMediator* scenes_;
  AirSprite* lifebar_;
  AirText* score_;
};

#endif
