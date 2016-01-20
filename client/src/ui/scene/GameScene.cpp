//
// SplashScene.cpp for SplashScene.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/src/ui/scene
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Thu Dec  3 11:05:20 2015 Théophile
// Last update Thu Dec  3 11:05:20 2015 Théophile
//

#include "GameScene.h"
#include "uistruct.h"

GameScene::GameScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes)
{
  ui_ = ui;
  window_ = window;
  res_ = resourceMediator;
  scenes_ = scenes;
    AirParticuleGenerator * particuleGenerator = new AirParticuleGenerator(Vector2f(-2, 0), 0.1, // vector start
                                                                         Vector2f(-2, 0), 0.1, // vector end
                                                                         sf::Color::White, 0, sf::Color::White, 0,  
                                                                         2, 2, // size
									 20000, 0, // life
									 20, // nb particules per secs
									 Vector2u(1280 + 360, 360), // pos particules
                                                                         360); // precision pos
  AirParticuleGenerator * particuleGenerator2 = new AirParticuleGenerator(Vector2f(-3, 0), 1, // vector start
                                                                          Vector2f(-3, 0), 1, // vector end
                                                                          sf::Color::White, 0, sf::Color::White, 0,
                                                                          2, 2, // size                              
                                                                          20000, 0, // life                          
                                                                          2, // nb particules per secs               
                                                                          Vector2u(1280 + 360, 360),
                                                                          360);
  score_ = new AirText(resourceMediator->getFontById(0), "0000", Vector2u(15, 40), sf::Color::Yellow, 20);
  lifebar_ = new AirSprite(resourceMediator->getPictureById(9), Vector2u(28, 15), Vector2u(308, 8));
  this->AddParticules(particuleGenerator);
  this->AddParticules(particuleGenerator2);
  this->AddEntity(new AirSprite(resourceMediator->getPictureById(8), Vector2u(10, 5), Vector2u(345, 30)));
  this->AddEntity(lifebar_);
  this->AddEntity(score_);
}

GameScene::~GameScene()
{

}

void GameScene::OnInit()
{
  hasLife = false;
  isPress_ = false;
  isDoublePress_ = false;
  isShot_ = false;
}

void GameScene::OnRender()
{
  for(unsigned int i = 0; i < this->entitys_.size(); ++i)
    {
      if (!this->entitys_[i]->checkUpdate())
	this->entitys_.erase(this->entitys_.begin()+i);
    }
  for(unsigned int i = 0; i < this->players_.size(); ++i)
    {
      if (!this->players_[i]->checkUpdate())
	this->players_.erase(this->players_.begin()+i);
    }
  if (!isDoublePress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(1));
      isDoublePress_ = true;
      isPress_ = false;
      return;
    }
  else if (!isDoublePress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(3));
      isDoublePress_ = true;
      isPress_ = false;
      return;
    }
  else if (!isDoublePress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(5));
      isDoublePress_ = true;
      isPress_ = false;
      return;
    }
  else if (!isDoublePress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(7));
      isDoublePress_ = true;
      isPress_ = false;
      return;
    }
  else if (isDoublePress_ && (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))))
    {
      isDoublePress_ = false;
      isPress_ = false;
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(8));
    }
  if (!isDoublePress_ && !isPress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(0));
      isPress_ = true;
    }
  else if (!isDoublePress_ && !isPress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {   
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(2));
      isPress_ = true;
    }  
  else if (!isDoublePress_ && !isPress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {   
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(4));
      isPress_ = true;
    }  
  else if (!isDoublePress_ && !isPress_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   
    {    
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(6));
      isPress_ = true;
    }
  else
    {
      if (isPress_ && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	  dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONPOSITIONUPDATE, new int(8));
	  isPress_ = false;
	}
    }

  if (!isShot_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      isShot_ = true;
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONSHOT, NULL);
    }
    else if (isShot_ && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      isShot_ = false;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONSENDROOMBACK, NULL);
      window_->SetScene(scenes_->getSceneByName("RoomScene"));    
    }
}

void GameScene::OnResize(Vector2u wsize)
{
  (void) wsize;
}

void GameScene::OnClick(void *)
{  

}

void GameScene::OnEvent(UiEvent event, void* data)
{
  (void)data;
  if (event == UiEvent::ONRETCONNECT)
    {      
    }
  else if (event == UiEvent::DISCONNECT)
    {
      window_->SetScene(scenes_->getSceneByName("ConnectionScene"));
    }
  else if (event == UiEvent::ONCREATEENTITY)
    {
      CreateEntity(data);
    }
  else if (event == UiEvent::ONUPDATEENTITY)
    {
      UpdateEntity(data);
    }
  else if (event == UiEvent::ONDESTROYENTITY)
    {
      DestroyEntity(data);
    }
  else if (event == UiEvent::ONSCORE)
    {
      score_->setTextString(Utils::to_string(*(int*)data));
    }
  else if (event == UiEvent::ONUPDATELIFE)
    {
      if (hasLife)
	{
	  life = *(int*)data;
	}
      else
	{
	  hasLife = true;
	  maxLife = *(int*)data;
	  life = *(int*)data;
	}
      lifebar_->SetSize(Vector2u((life * 308) / maxLife, 8));
    }
  else if (event == UiEvent::ONFINALSCORE)
    window_->SetScene(scenes_->getSceneByName("ScoreScene"));
}

void GameScene::CreateEntity(void* data)
{
  ParamEntity *PEntity = (ParamEntity*)data;
  if (PEntity->id_sprite == 10)
    window_->PlaySoundA(res_->getSoundById(0));
  if (PEntity->id < 4)
    this->players_.push_back(new Player(this, res_, PEntity->id, PEntity->x,PEntity->y,PEntity->rot, PEntity->size_x,PEntity->size_y, PEntity->id_sprite, PEntity->name));
  else
    this->entitys_.push_back(new Entity(this, res_, PEntity->id, PEntity->x,PEntity->y,PEntity->rot, PEntity->size_x,PEntity->size_y, PEntity->id_sprite, PEntity->name));
}

void GameScene::UpdateEntity(void* data)
{
  ParamEntity *PEntity = (ParamEntity*)data;
  if (PEntity->id_sprite == 12)
    window_->PlaySoundA(res_->getSoundById(1)); 
  if (PEntity->id < 4)
    for(unsigned int i = 0; i < this->players_.size(); ++i)
      {
	if (this->players_[i]->getId() == PEntity->id)
	  this->players_[i]->Update(PEntity->id, PEntity->x, PEntity->y, PEntity->rot, PEntity->id_sprite);
      }
  else
    {
      for(unsigned int i = 0; i < this->entitys_.size(); ++i)
	{
	  if (this->entitys_[i]->getId() == PEntity->id)
	    {
	      this->entitys_[i]->Update(PEntity->id, PEntity->x, PEntity->y, PEntity->rot, PEntity->id_sprite);
	      return;
	    }
	}
      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONSENDCREATEENTITY, &(PEntity->id));
    }
}

void GameScene::DestroyEntity(void* data)
{
  ParamEntity *PEntity = (ParamEntity*)data;
  if (PEntity->id < 4)
    for(unsigned int i = 0; i < this->players_.size(); ++i)
      {
	if (this->players_[i]->getId() == PEntity->id)
	  {
	    this->players_[i]->Destroy();
	    this->players_.erase(this->players_.begin()+i);
	    return;
	  }
      }
  else
    for(unsigned int i = 0; i < this->entitys_.size(); ++i)
      {
	if (this->entitys_[i]->getId() == PEntity->id)
	  {
	    this->entitys_[i]->Destroy();
	    this->entitys_.erase(this->entitys_.begin()+i);
	  }
      }
}
