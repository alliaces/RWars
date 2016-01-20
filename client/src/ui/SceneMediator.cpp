#include "SplashScene.h"
#include "ConnectionScene.h"
#include "SceneMediator.h"
#include "RoomScene.h"
#include "WaitScene.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "Ui.h"

SceneMediator::SceneMediator(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator)
{
  this->scenes_["SplashScene"] = new SplashScene(ui, window, resourceMediator, this);
  this->scenes_["ConnectionScene"] = new ConnectionScene(ui, window, resourceMediator, this);
  this->scenes_["RoomScene"] = new RoomScene(ui, window, resourceMediator, this);
  this->scenes_["WaitScene"] = new WaitScene(ui, window, resourceMediator, this);
  this->scenes_["GameScene"] = new GameScene(ui, window, resourceMediator, this);
  this->scenes_["ScoreScene"] = new ScoreScene(ui, window, resourceMediator, this);
  this->resourceMediator_ = resourceMediator;
}

SceneMediator::~SceneMediator()
{
}

AScene *SceneMediator::getSceneByName(const std::string &name)
{
  return (this->scenes_[name]);
}
