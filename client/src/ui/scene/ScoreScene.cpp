//
// ScoreScene.cpp for ScoreScene.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/src/ui/scene
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Mon Dec 21 02:00:55 2015 Théophile
// Last update Mon Dec 21 02:00:55 2015 Théophile
//

#include "ScoreScene.h"

ScoreScene::ScoreScene(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator, SceneMediator* scenes)
{
	  ui_ = ui;
	  window_ = window;
	  this->resourceMediator_ = resourceMediator;
	  scenes_ = scenes;
	  AirText* title = new AirText(resourceMediator->getFontById(0), "R-Wars - Score", Vector2u(430, 110), sf::Color::Yellow, 50);

	  AirSprite* frame = new AirSprite(resourceMediator->getPictureById(1), Vector2u(350, 200), Vector2u(600, 300));

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
	  AirText* gameOverText = new AirText(resourceMediator->getFontById(0), "Game Over", Vector2u(550, 220), sf::Color::Black, 30);
	  AirText* scoreText = new AirText(resourceMediator->getFontById(0), "Your Score is ", Vector2u(500, 350), sf::Color::Black, 20);
	  this->finalScore_ = new AirText(resourceMediator->getFontById(0), "0", Vector2u(670, 350), sf::Color::Yellow, 20);

	  this->AddEntity(frame);
	  this->AddParticules(particuleGenerator);
	  this->AddParticules(particuleGenerator2);
	  this->AddEntity(title);
	  this->AddEntity(gameOverText);
	  this->AddEntity(scoreText);
}

ScoreScene::~ScoreScene()
{
}

void ScoreScene::OnInit()
{

}

void ScoreScene::OnRender()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->resourceMediator_->getMusicById(1)->stopMusic();
		this->window_->RemoveMusic(this->resourceMediator_->getMusicById(1));
		this->window_->AddMusic(this->resourceMediator_->getMusicById(0));
		this->window_->SetScene(scenes_->getSceneByName("RoomScene"));
	}
}

void ScoreScene::OnResize(Vector2u wsize)
{
	(void) wsize;
}

void ScoreScene::OnClick(void *)
{
}

void ScoreScene::OnEvent(UiEvent event, void* data)
{
	  if (event == UiEvent::ONFINALSCORE)
	    {
		  this->finalScore_->setTextString(Utils::to_string(*((int*)data)));
		  this->AddEntity(this->finalScore_);
	    }
}
