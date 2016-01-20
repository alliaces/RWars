//
// SplashScene.cpp for SplashScene.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/src/ui/scene
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Thu Dec  3 11:05:20 2015 Théophile
// Last update Thu Dec  3 11:05:20 2015 Théophile
//

#include "SplashScene.h"
#include "SceneMediator.h"
#include <ctime>

SplashScene::SplashScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes)
{
  time_ = 0;
  isPressVisible = true;
  (void) ui;
  window_ = window;
  scenes_ = scenes;
  this->window_->AddMusic(resourceMediator->getMusicById(0));
  AirText *title = new AirText(resourceMediator->getFontById(0), "R-Wars", Vector2u(500, 60), sf::Color::Yellow, 80);
  AirText *cop = new AirText(resourceMediator->getFontById(0),
			     "Copyright allee_r, lelong_t, blonde_f, couill_b, ardoui_t, lamart_m",
			     Vector2u(420, 680), sf::Color::Yellow, 12);
  press = new AirText(resourceMediator->getFontById(0),
			     "Press ENTER to start",
			     Vector2u(510, 450), sf::Color::Yellow, 20);
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
  this->AddEntity(title);
  this->AddEntity(cop);
  this->AddEntity(press);
  this->AddParticules(particuleGenerator);
  this->AddParticules(particuleGenerator2);
}

SplashScene::~SplashScene()
{
}

void SplashScene::OnInit()
{
  time_ = 0;
}

void SplashScene::OnRender()
{
  unsigned int sysTime = time(NULL) * 1000;
  unsigned int ptime = sysTime - time_;
  if (ptime >= 1000)
    {
      time_ = time(NULL) * 1000;
      if (isPressVisible)
	{
	  isPressVisible = false;
	  press->setTextString("");
	}
      else
	{
	  isPressVisible = true;
	  press->setTextString("Press ENTER to start");
	}
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    window_->SetScene(scenes_->getSceneByName("ConnectionScene"));
}

void SplashScene::OnResize(Vector2u wsize)
{
	(void) wsize;
}

void SplashScene::OnEvent(UiEvent event, void* data)
{
  std::cout << "return splash" << std::endl;
  (void)event;
  (void)data;
}
