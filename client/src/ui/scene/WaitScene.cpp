//
// SplashScene.cpp for SplashScene.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/src/ui/scene
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Thu Dec  3 11:05:20 2015 Théophile
// Last update Thu Dec  3 11:05:20 2015 Théophile
//

#include "WaitScene.h"

WaitScene::WaitScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes)
{
  ui_ = ui;
  window_ = window;
  this->resourceMediator_ = resourceMediator;
  scenes_ = scenes;
  this->timerNotify_ = 0;
  this->isNotifyDisplay_ = false;
  AirText* title = new AirText(resourceMediator->getFontById(0), "R-Wars - Wait", Vector2u(430, 110), sf::Color::Yellow, 50);
  AirSprite* frame = new AirSprite(resourceMediator->getPictureById(1), Vector2u(410, 200), Vector2u(430, 120));
  this->textNotify_ = new AirText(this->resourceMediator_->getFontById(0),
										"",
										Vector2u(10, 700),
										sf::Color::Yellow,
										15);
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

  this->quitRoomButton_ = new AirButton(this->resourceMediator_->getPictureById(2),
    this->resourceMediator_->getPictureById(3),
    Vector2u(670, 280),
    Vector2u(100, 30),
    this->resourceMediator_->getFontById(0));
  this->quitRoomButton_->setText("Quit", sf::Color::Black, 15);
  this->quitRoomButton_->onClickHandler(this);

  this->readyRoomButton_ = new AirButton(this->resourceMediator_->getPictureById(2),
    this->resourceMediator_->getPictureById(3),
    Vector2u(470, 280),
    Vector2u(100, 30),
    this->resourceMediator_->getFontById(0));
  this->readyRoomButton_->setText("Ready", sf::Color::Black, 15);
  this->readyRoomButton_->onClickHandler(this);

  this->initPlayerText();

  this->AddEntity(frame);
  this->AddEntity(title);
  this->AddParticules(particuleGenerator);
  this->AddParticules(particuleGenerator2);
  this->AddEntity(this->quitRoomButton_);
  this->AddEntity(this->readyRoomButton_);
}

WaitScene::~WaitScene()
{

}

void WaitScene::initPlayerText()
{
	this->playersInRoom_.push_back(new AirText(this->resourceMediator_->getFontById(0),
			"P1",
			Vector2u(450, 220),
			sf::Color::Blue,
			30));

	this->playersInRoom_.push_back(new AirText(this->resourceMediator_->getFontById(0),
			"P2",
			Vector2u(450 + 100, 220),
			sf::Color::Red,
			30));

	this->playersInRoom_.push_back(new AirText(this->resourceMediator_->getFontById(0),
			"P3",
			Vector2u(450 + 200, 220),
			sf::Color::Yellow,
			30));

	this->playersInRoom_.push_back(new AirText(this->resourceMediator_->getFontById(0),
			"P4",
			Vector2u(450 + 300, 220),
			sf::Color::Green,
			30));
}

void WaitScene::OnInit()
{
  this->nbPlayerInRoom = 0;
  for (unsigned int i = 0; i < this->playersInRoom_.size(); ++i)
    this->RemoveEntity(this->playersInRoom_[i]);
}

void WaitScene::OnRender()
{
	if (this->isNotifyDisplay_ == true)
	{
		this->timerNotify_++;
		if (this->timerNotify_ == 120)
		{
			this->timerNotify_ = 0;
			this->isNotifyDisplay_ = false;
			this->RemoveEntity(this->textNotify_);
		}
	}
}

void WaitScene::OnResize(Vector2u wsize)
{
  (void) wsize;
}

void WaitScene::OnClick(void *arg)
{
	if (arg == this->quitRoomButton_)
	  {
	    dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONLEAVEROOM, NULL);
	    for (int i = 0;i < this->nbPlayerInRoom; ++i)
	      this->RemoveEntity(playersInRoom_[i]);
	    this->window_->SetScene(scenes_->getSceneByName("RoomScene"));
	  }	
	if (arg == this->readyRoomButton_)
	  {
	    dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONREADY, NULL);
	  }
}

void WaitScene::OnEvent(UiEvent event, void* data)
{
  (void)data;
  if (event == UiEvent::STARTGAME)
    {
	  window_->SetScene(scenes_->getSceneByName("GameScene"));
	  this->resourceMediator_->getMusicById(0)->stopMusic();
	  this->window_->RemoveMusic(this->resourceMediator_->getMusicById(0));
	  this->window_->AddMusic(this->resourceMediator_->getMusicById(1));
    }
  else if (event == UiEvent::PLAYERJOIN)
    {
	  if (this->nbPlayerInRoom < 4)
	  {
		  this->isNotifyDisplay_ = true;
		  this->textNotify_->setTextString("Player has just joined");
		  this->AddEntity(this->textNotify_);
		  this->AddEntity(playersInRoom_[this->nbPlayerInRoom]);
		  this->nbPlayerInRoom++;
	  }
    }
  else if (event == UiEvent::PLAYERQUIT)
    {
	  if (this->nbPlayerInRoom > 0)
	  {
		  this->isNotifyDisplay_ = true;
		  this->textNotify_->setTextString("Player has just left");
		  this->AddEntity(this->textNotify_);
		  this->nbPlayerInRoom--;
	    this->RemoveEntity(playersInRoom_[this->nbPlayerInRoom]);
	  }
    }
  else if (event == UiEvent::DISCONNECT)
    {
      window_->SetScene(scenes_->getSceneByName("ConnectionScene"));
    }
}
