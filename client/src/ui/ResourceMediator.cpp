#include "ResourceMediator.h"
#ifndef _WIN32
#include "LinuxFileHandler.h"
#else
#include "WindowsFileHandler.h"
#endif
#include <sstream>
#include <iostream>

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> internal;
  std::stringstream ss(str); // Turn the string into a stream.
  std::string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}


ResourceMediator::ResourceMediator()
{
  
  AFileHandler *file;
#ifndef _WIN32
  file = new LinuxFileHandler("resources/sprites/config.cfg");
#else
  file = new WindowsFileHandler("resources/sprites/config.cfg");
#endif

  file->openFile(0);

  this->fonts_[0] = new AirFont("resources/fonts/STARWARS.TTF");
  std::string str = file->readFile(file->getFileSize());
  std::istringstream f(str);
  std::string line;
  while (std::getline(f, line)) {
    this->resources_[std::atoi(split(line, ':')[0].c_str())] = new AirPicture(split(line, ':')[1]);
  }
  this->musics_[0] = new AirMusic("resources/musics/02 - John Williams - Main TitleRebel Blockade Runner.ogg");
  this->musics_[1] = new AirMusic("resources/musics/Spice Opera.ogg");
  this->sounds_[0] = new AirSound("resources/musics/laser.wav");
  this->sounds_[1] = new AirSound("resources/musics/explosion.wav");
}

ResourceMediator::~ResourceMediator()
{
	int i(0);

	while ((size_t) i < this->fonts_.size())
	{
		delete this->fonts_[i];
		i++;
	}

	i = 0;
	while ((size_t) i < this->resources_.size())
	{
		delete this->resources_[i];
		i++;
	}

	i = 0;
	while ((size_t) i < this->musics_.size())
	{
		this->musics_[i]->stopMusic();
		delete this->musics_[i];
		i++;
	}

	i = 0;
	while ((size_t) i < this->sounds_.size())
	{
		this->sounds_[i]->stopSound();
		delete this->sounds_[i];
		i++;
	}
}

AirPicture *ResourceMediator::getPictureById(int id)
{
  if (this->resources_.find(id) == this->resources_.end())
    return (new AirPicture(""));
  return (this->resources_[id]);
}

AirFont *ResourceMediator::getFontById(int id)
{
	return (this->fonts_[id]);
}

IAirMusic *ResourceMediator::getMusicById(int id)
{
	return (this->musics_[id]);
}

IAirSound *ResourceMediator::getSoundById(int id)
{
	return (this->sounds_[id]);
}
