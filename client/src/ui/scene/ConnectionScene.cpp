//
// SplashScene.cpp for SplashScene.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/src/ui/scene
//
// Made by Théophile
// Login   <lelong_t@epitech.net>
//
// Started on  Thu Dec  3 11:05:20 2015 Théophile
// Last update Thu Dec  3 11:05:20 2015 Théophile
//

#include "ConnectionScene.h"
#include "uistruct.h"

ConnectionScene::ConnectionScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes)
{
  ui_ = ui;
  window_ = window;
  this->resourceMediator_ = resourceMediator;
  scenes_ = scenes;
  AirText* title = new AirText(resourceMediator->getFontById(0), "R-Wars - Connection", Vector2u(380, 110), sf::Color::Yellow, 50);

  AirText* lblip = new AirText(resourceMediator->getFontById(0), "Ip    : ", Vector2u(480, 280), sf::Color::Black, 20);
  this->ip_ = new AirTextBox(resourceMediator->getPictureById(0), Vector2u(560, 280), Vector2u(250, 30), resourceMediator->getFontById(0));

  AirText* lblport = new AirText(resourceMediator->getFontById(0), "Port : ", Vector2u(480, 320), sf::Color::Black, 20);
  this->port_ = new AirTextBox(resourceMediator->getPictureById(0), Vector2u(560, 320), Vector2u(250, 30), resourceMediator->getFontById(0));

  AirButton* connectbtn = new AirButton(resourceMediator->getPictureById(2), resourceMediator->getPictureById(3), Vector2u(590, 400), Vector2u(150, 30), resourceMediator->getFontById(0));
  connectbtn->setText("Connect", sf::Color::Black, 15);
  connectbtn->onClickHandler(this);

  AirSprite* frame = new AirSprite(resourceMediator->getPictureById(1), Vector2u(350, 200), Vector2u(600, 300));

  this->rememberConnection();

  lblerror = new AirText(resourceMediator->getFontById(0), "", Vector2u(600, 430), sf::Color::Red, 12);

  AirParticuleGenerator * particuleGenerator = new AirParticuleGenerator(Vector2f(-2, 0), 0.1, // vector start
									 Vector2f(-2, 0), 0.1, // vector end
									 sf::Color::White, 0, sf::Color::White, 0, // color
									 2, 2, // size
									 20000, 0, // life
									 20, // nb particules per secs
									 Vector2u(1280 + 360, 360), // pos particules
									 360); // precision pos
  AirParticuleGenerator * particuleGenerator2 = new AirParticuleGenerator(Vector2f(-3, 0), 1, // vector start
									  Vector2f(-3, 0), 1, // vector end
									  sf::Color::White, 0, sf::Color::White, 0, // color
									  2, 2, // size
									  20000, 0, // life
									  2, // nb particules per secs
									  Vector2u(1280 + 360, 360), // pos particules
									  360);

  this->AddEntity(frame);
  this->AddParticules(particuleGenerator);
  this->AddParticules(particuleGenerator2);
  this->AddEntity(this->rememberServer_);
  this->AddEntity(this->rememberServerConnection_);
  this->AddEntity(title);
  this->AddEntity(lblip);
  this->AddEntity(this->ip_);
  this->AddEntity(lblport);
  this->AddEntity(this->port_);
  this->AddEntity(connectbtn);
  this->AddEntity(lblerror);
}

ConnectionScene::~ConnectionScene()
{
}

void ConnectionScene::rememberConnection()
{
	#ifdef __linux__
	  this->fileHandler_ = new LinuxFileHandler("resources/ConnectionConfigs.txt");
	#endif
  #ifdef _WIN32
    this->fileHandler_ = new WindowsFileHandler("resources/ConnectionConfigs.txt");
  #endif

	  this->rememberServer_ = new AirCheckBox(this->resourceMediator_->getPictureById(5),
			  this->resourceMediator_->getPictureById(2),
			  Vector2u(475, 370), Vector2u(15, 15));
	  this->rememberServer_->onClickHandler(this);

	  this->rememberServerConnection_ = new AirText(this->resourceMediator_->getFontById(0),
			  "Remember Connection",
			  Vector2u(500, 370),
			  sf::Color::Black,
			  15);
	  this->readConnectionConfigs();
}

void ConnectionScene::readConnectionConfigs()
{
	  if (this->fileHandler_->openFile(0) == true)
	  {
		  std::string tmp = this->fileHandler_->readFile(this->fileHandler_->getFileSize());


		  std::vector<std::string> tmpIpAdress = UtilsSplit::split(tmp, ':');

		  if (tmpIpAdress.size() != 2)
		  {
			  this->ip_->setText("", sf::Color::Black, 15);
			  this->port_->setText("", sf::Color::Black, 15);
		  }
		  else
		  {
			  size_t find(0);

			  while ((find = tmpIpAdress[1].find('\n')) != std::string::npos)
				  tmpIpAdress[1].erase(find, 1);

			  this->ip_->setText(tmpIpAdress[0], sf::Color::Black, 15);
			  this->port_->setText(tmpIpAdress[1], sf::Color::Black, 15);
			  this->fileHandler_->closeFile();
		  }
	  }
	  else
	  {
		  this->ip_->setText("", sf::Color::Black, 15);
		  this->port_->setText("", sf::Color::Black, 15);
	  }
}

void ConnectionScene::writeConnectionConfigs()
{
	  if (this->fileHandler_->openFile(1) == true)
	  {
		  this->fileHandler_->writeFile(this->ip_->getString() + ":" + this->port_->getString());
		  this->fileHandler_->closeFile();
	  }
}

void ConnectionScene::OnInit()
{

}

void ConnectionScene::OnRender()
{
}

void ConnectionScene::OnResize(Vector2u wsize)
{
	(void) wsize;
}

void ConnectionScene::OnClick(void *)
{
  Param *param;
  param = new Param;
  param->ip = this->ip_->getString();
  param->port = this->port_->getString();
  if (this->rememberServer_->getIsChecked() == true)
	  this->writeConnectionConfigs();
  dynamic_cast<IUiListener*>(ui_)->OnEvent(UiEvent::ONCONNECT, param);
}

void ConnectionScene::OnEvent(UiEvent event, void* data)
{
  if (event == UiEvent::ONRETCONNECT)
    {
      if (data != NULL)
	lblerror->setTextString((char*)data);
      else
	{
	  window_->SetScene(scenes_->getSceneByName("RoomScene"));
	}
    }
}
