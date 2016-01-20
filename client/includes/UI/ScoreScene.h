/*
** ScoreScene.h for ScoreScene.h in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/includes/UI
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Mon Dec 21 02:01:31 2015 Théophile
** Last update Mon Dec 21 02:01:59 2015 Théophile
*/

#ifndef		SCORESCENE_H_
# define	SCORESCENE_H_

#include <AirEngine.h>
#include "Ui.h"
#include "IUiListener.h"
#include "Utils.h"

class Ui;

class ScoreScene : public AScene, public OnClickListener, public IUiListener
{
public:
	ScoreScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes);
  ~ScoreScene();
  void OnInit();
  void OnRender();
  void OnResize(Vector2u wsize);
  void OnClick(void *);
  void OnEvent(UiEvent event, void*);
private:
  Ui* ui_;
  SceneMediator* scenes_;
  ResourceMediator *resourceMediator_;
  AirWindow* window_;
  AirText* finalScore_;
};

#endif
