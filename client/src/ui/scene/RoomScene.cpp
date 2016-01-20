//
// SplashScene.cpp for SplashScene.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/src/ui/scene
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Thu Dec  3 11:05:20 2015 Théophile
// Last update Thu Dec  3 11:05:20 2015 Théophile
//

#include "RoomScene.h"

RoomScene::RoomScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes)
{
  this->createRoomButton_ = NULL;
  this->refreshButton_ = NULL;
  this->cancelButton_ = NULL;
  this->okButton_ = NULL;
  this->ui_ = ui;
  this->resourceMediator_ = resourceMediator;
  window_ = window;
  scenes_ = scenes;
  AirText* title = new AirText(resourceMediator->getFontById(0), "R-Wars - Room", Vector2u(430, 110), sf::Color::Yellow, 50);
  this->timerNotify_ = 0;
  this->isNotifyDisplay_ = false;
  this->textNotify_ = new AirText(this->resourceMediator_->getFontById(0),
										"",
										Vector2u(10, 700),
										sf::Color::Red,
										15);
  this->initRoomScreen();

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

  this->posPageRoom_ = 0;
  this->nbPageRoom_ = 1;
  this->frameUpPress_ = 0;
  this->frameDownPress_ = 0;
  this->posLastButtonRoom_ = 0;
  this->maxPosLastButtonRoom_ = 8 * 31;

  this->AddEntity(title);
  this->AddParticules(particuleGenerator);
  this->AddParticules(particuleGenerator2);
}

RoomScene::~RoomScene()
{

}

void RoomScene::initRoomScreen()
{
	  this->roomFrame_ = new AirSprite(this->resourceMediator_->getPictureById(1), Vector2u(350, 200), Vector2u(600, 340));

	  this->refreshButton_ = new AirButton(this->resourceMediator_->getPictureById(2),
	    this->resourceMediator_->getPictureById(3),
	    Vector2u(371, 220 + 9 * 31),
	    Vector2u(559 / 3, 30),
	    this->resourceMediator_->getFontById(0));
	  this->refreshButton_->setText("Refresh", sf::Color::Black, 15);
	  this->refreshButton_->onClickHandler(this);

	  this->createRoomButton_ = new AirButton(this->resourceMediator_->getPictureById(2),
	    this->resourceMediator_->getPictureById(3),
	    Vector2u(371 + (559 / 3 * 2), 220 + 9 * 31),
	    Vector2u(559 / 3, 30),
	    this->resourceMediator_->getFontById(0));
	  this->createRoomButton_->setText("Create", sf::Color::Black, 15);
	  this->createRoomButton_->onClickHandler(this);

	  this->AddEntity(this->roomFrame_);
	  this->AddEntity(this->refreshButton_);
	  this->AddEntity(this->createRoomButton_);
}

void RoomScene::initCreateRoomScreen()
{
	this->roomCreationFrame_ = new AirSprite(this->resourceMediator_->getPictureById(1), Vector2u(300, 200 + 100), Vector2u(700, 180));

	this->roomCreation_ = new AirText(this->resourceMediator_->getFontById(0),
										"Room Title",
										Vector2u(371, 220 + 3 * 31),
										sf::Color::Black,
										15);

	this->okButton_ = new AirButton(this->resourceMediator_->getPictureById(2),
	    this->resourceMediator_->getPictureById(3),
	    Vector2u(371, 220 + 7 * 31),
	    Vector2u(559 / 3, 30),
	    this->resourceMediator_->getFontById(0));
	  this->okButton_->setText("Ok", sf::Color::Black, 15);
	  this->okButton_->onClickHandler(this);

	this->cancelButton_ = new AirButton(this->resourceMediator_->getPictureById(2),
		    this->resourceMediator_->getPictureById(3),
		    Vector2u(371 + (559 / 3 * 2), 220 + 7 * 31),
		    Vector2u(559 / 3, 30),
		    this->resourceMediator_->getFontById(0));
	this->cancelButton_->setText("Cancel", sf::Color::Black, 15);
	this->cancelButton_->onClickHandler(this);

	this->newRoomTitle_ = new AirTextBox(this->resourceMediator_->getPictureById(0),
										Vector2u(371, 220 + 4 * 31),
										Vector2u(559, 30),
										this->resourceMediator_->getFontById(0));
	this->newRoomTitle_->setText("", sf::Color::Black, 15);

	for (size_t i = 0; i < this->roomsButtons_.size(); i++)
		this->roomsButtons_[i]->setEnable(false);

	this->AddEntity(this->roomCreationFrame_);
	this->AddEntity(this->roomCreation_);
	this->AddEntity(this->okButton_);
	this->AddEntity(this->cancelButton_);
	this->AddEntity(this->newRoomTitle_);
}

void RoomScene::removeCreateRoomScreen()
{
	for (size_t i = 0; i < this->roomsButtons_.size(); i++)
		this->roomsButtons_[i]->setEnable(true);
	this->RemoveEntity(this->roomCreationFrame_);
	this->RemoveEntity(this->roomCreation_);
	this->RemoveEntity(this->okButton_);
	this->RemoveEntity(this->cancelButton_);
	this->RemoveEntity(this->newRoomTitle_);
}

void RoomScene::addRoomScreen()
{
	std::string tmpTitle(this->newRoomTitle_->GetText()->getString());

	dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONCREATEROOM, (void*)tmpTitle.c_str());
	dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONJOINROOM, (void*)tmpTitle.c_str());	
	this->removeCreateRoomScreen();
}

void RoomScene::refreshRoomScreen()
{
  this->posLastButtonRoom_ = 0;
  for (unsigned int i = 0; i < this->roomsButtons_.size(); ++i)
    {
      this->RemoveEntity(this->roomsButtons_[i]);
    }
  this->roomsButtons_.clear();
  this->posPageRoom_ = 0;
  this->nbPageRoom_ = 1;
  dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONREFRESHROOM, NULL);
}

void RoomScene::OnInit()
{
  refreshRoomScreen();
}

void RoomScene::OnRender()
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->posPageRoom_ > 0 and this->frameUpPress_ >= 5)
		{
			int i;

			i = this->posPageRoom_ * 9;
			while ((size_t)i < this->roomsButtons_.size() and i < this->posPageRoom_ * 9 + 9)
			{
				this->RemoveEntity(this->roomsButtons_[i]);
				i++;
			}

			this->posPageRoom_--;
			i = this->posPageRoom_ * 9;
			while ((size_t)i < this->roomsButtons_.size() and i < this->posPageRoom_ * 9 + 9)
			{
				this->AddEntity(this->roomsButtons_[i]);
				i++;
			}
			this->frameUpPress_ = 0;
		}
		else
			this->frameUpPress_++;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->posPageRoom_ < this->nbPageRoom_ - 1 and this->frameDownPress_ >= 5)
		{
			int i;

			i = this->posPageRoom_ * 9;
			while ((size_t)i < this->roomsButtons_.size() and i < this->posPageRoom_ * 9 + 9)
			{
				this->RemoveEntity(this->roomsButtons_[i]);
				i++;
			}
			this->posPageRoom_++;
			i = this->posPageRoom_ * 9;
			while ((size_t)i < this->roomsButtons_.size() and i < this->posPageRoom_ * 9 + 9)
			{
				this->AddEntity(this->roomsButtons_[i]);
				i++;
			}
			this->frameDownPress_ = 0;
		}
		else
			this->frameDownPress_++;
	}
}

void RoomScene::OnResize(Vector2u wsize)
{
  (void) wsize;
}

void RoomScene::OnClick(void *arg)
{
  if (this->createRoomButton_ && (AirButton*)arg == this->createRoomButton_)
	  this->initCreateRoomScreen();
  else if (this->refreshButton_ && (AirButton*)arg == this->refreshButton_)
	  this->refreshRoomScreen();
  else if (this->cancelButton_ && (AirButton*)arg == this->cancelButton_)
	  this->removeCreateRoomScreen();
  else if (this->okButton_ && (AirButton*)arg == this->okButton_)
  {
	  if (this->newRoomTitle_->getString() != "")
		  this->addRoomScreen();
  }
  else
    {
      for (unsigned int i = 0; i < this->roomsButtons_.size(); ++i)
	{
	  if ((AirButton*) arg == this->roomsButtons_[i])
	    {
	      std::string tmpTitle(((AirButton*)arg)->GetText()->getString());
	      tmpTitle = tmpTitle.erase(tmpTitle.find_last_of(" ") ,tmpTitle.size()); 
	      dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONJOINROOM, (void*)tmpTitle.c_str());
	    }
	}
    }
}

void RoomScene::OnEvent(UiEvent event, void* data)
{
  if (event == UiEvent::ONRECEIVEROOM)
    {
	  this->roomsButtons_.push_back(new AirButton(this->resourceMediator_->getPictureById(4),
			  this->resourceMediator_->getPictureById(5),
			  Vector2u(371, 220 + this->posLastButtonRoom_),
			  Vector2u(559, 30),
			  this->resourceMediator_->getFontById(0)));
	  this->roomsButtons_[this->roomsButtons_.size() - 1]->setText((char *) data, sf::Color::Black, 15);
	  this->roomsButtons_[this->roomsButtons_.size() - 1]->onClickHandler(this);
	  if (this->posLastButtonRoom_ >= this->maxPosLastButtonRoom_)
	  {
		  this->posLastButtonRoom_ = 0;
		  this->nbPageRoom_++;
	  }
	  else
	  {
		  this->posLastButtonRoom_ += 31;
		  if (this->roomsButtons_.size() < 10)
			  this->AddEntity(this->roomsButtons_[this->roomsButtons_.size() - 1]);
	  }
    }
  else if (event == UiEvent::ONRETJOINROOM)
    {
      window_->SetScene(scenes_->getSceneByName("WaitScene"));
    }
  else if (event == UiEvent::ONRECEIVEWRONGROOM)
  {
	  this->roomsButtons_.push_back(new AirButton(this->resourceMediator_->getPictureById(4),
			  this->resourceMediator_->getPictureById(5),
			  Vector2u(371, 220 + this->posLastButtonRoom_),
			  Vector2u(559, 30),
			  this->resourceMediator_->getFontById(0)));
	  this->roomsButtons_[this->roomsButtons_.size() - 1]->setText((char *) data, sf::Color::Red, 15);
	  this->roomsButtons_[this->roomsButtons_.size() - 1]->onClickHandler(this);
	  this->roomsButtons_[this->roomsButtons_.size() - 1]->setEnable(false);
	  if (this->posLastButtonRoom_ >= this->maxPosLastButtonRoom_)
	  {
		  this->posLastButtonRoom_ = 0;
		  this->nbPageRoom_++;
	  }
	  else
	  {
		  this->posLastButtonRoom_ += 31;
		  if (this->roomsButtons_.size() < 10)
			  this->AddEntity(this->roomsButtons_[this->roomsButtons_.size() - 1]);
	  }
  }
  else if (event == UiEvent::ONRETCREATEROOMERROR)
  {
	  this->isNotifyDisplay_ = true;
	  this->textNotify_->setTextString("Room creation error");
	  this->AddEntity(this->textNotify_);
  }
  else if (event == UiEvent::DISCONNECT)
    {
      window_->SetScene(scenes_->getSceneByName("ConnectionScene"));
    }
}
