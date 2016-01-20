#include "AirWindow.h"
#include "AScene.h"
#include <iostream>

AirWindow::~AirWindow()
{
    //dtor
}

AirWindow::AirWindow(std::string title, const Vector2u& wsize) : _window(sf::VideoMode(wsize.X, wsize.Y), title)
{
  _window.setFramerateLimit(60);
    _window.setActive(false);
  _scene = NULL;
}

bool AirWindow::IsOpen()
{
    return (_window.isOpen());
}

void AirWindow::SetSize(const Vector2u& wsize)
{
    _window.setSize(sf::Vector2u(wsize.X, wsize.Y));
    if (_scene)
        _scene->OnResize(wsize);
}

void AirWindow::SetTitle(const std::string& title)
{
    _window.setTitle(title);
    _title = title;
}

const std::string& AirWindow::GetTitle() const
{
    return (_title);
}

Vector2u AirWindow::GetSize() const
{
    return (Vector2u(_window.getSize().x, _window.getSize().y));
}

void AirWindow::SetScene(AScene* scene)
{
    _scene = scene;
    _scene->OnInit();
}

AScene* AirWindow::GetScene()
{
  return(_scene);
}

void AirWindow::AddMusic(IAirMusic *music)
{
	this->_musics[music->getMusicName()] = music;
	this->_musics[music->getMusicName()]->playMusic();
}

void AirWindow::RemoveMusic(IAirMusic *music)
{
	std::map<std::string, IAirMusic*>::iterator it;

	it = this->_musics.find(music->getMusicName());
	if (it != this->_musics.end())
	{
		this->_musics[music->getMusicName()]->stopMusic();
		this->_musics.erase(it);
	}
}

void AirWindow::PlaySoundA(IAirSound *sound)
{
  sound->playSound();
}

sf::RenderWindow& AirWindow::GetWindows()
{
  return (_window);
}

void AirWindow::Update()
{
    if (_window.isOpen())
    {
      sf::Event event;
      while (_window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    _window.close();
        }
      _window.clear();
      if (_scene != NULL)
        {	  
	  _scene->OnRender();
	  for (unsigned int i = 0; i < _scene->GetParticules().size(); ++i)
            {
	      _scene->GetParticules()[i]->Update();
	      for (unsigned int j = 0; j < _scene->GetParticules()[i]->GetAllShape().size(); ++j)
		_window.draw(*_scene->GetParticules()[i]->GetAllShape()[j]->GetShape());
	    }
	  for (unsigned int i = 0; i < _scene->GetEntitys().size(); ++i)
            {
	      
	      if (_scene->GetEntitys()[i]->GetSprite())
		_window.draw(*_scene->GetEntitys()[i]->GetSprite());
	      if (_scene->GetEntitys()[i]->GetText())
		_window.draw(*_scene->GetEntitys()[i]->GetText());
	      _scene->GetEntitys()[i]->Update(*this);          
	    }
        }
      _window.display();
    }
}

