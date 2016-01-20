#include "AirMusic.h"

AirMusic::AirMusic(const std::string &musicName)
{
	this->musicName_  = musicName;
	this->music_.openFromFile(this->musicName_);
	this->music_.setLoop(1);
}

AirMusic::~AirMusic()
{
}

/*
** getters / setters
*/

const std::string &AirMusic::getMusicName() const
{
	return (this->musicName_);
}

void AirMusic::setVolumeMusic(float volume)
{
	this->music_.setVolume(volume);
}

float AirMusic::getVolumeMusic() const
{
	return (this->music_.getVolume());
}

void AirMusic::setLoopMusic(bool loop)
{
	this->music_.setLoop(loop);
}

bool AirMusic::getLoopMusic() const
{
	return (this->music_.getLoop());
}

/*
** open music from file
*/
bool AirMusic::openFromFile()
{
	return (this->music_.openFromFile(this->musicName_));
}

/*
** play music
*/
void AirMusic::playMusic()
{
	this->music_.play();
}

/*
** pause music
*/
void AirMusic::pauseMusic()
{
	this->music_.pause();
}

/*
** stop music
*/
void AirMusic::stopMusic()
{
	this->music_.stop();
}
