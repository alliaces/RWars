#include "AirSound.h"

AirSound::AirSound(const std::string &soundName)
{
	this->soundName_ = soundName;
	this->loadSoundFromFile();
}

AirSound::~AirSound()
{
}

bool AirSound::loadSoundFromFile()
{
	if (!this->buffer_.loadFromFile(this->soundName_))
		return (false);
	this->sound_.setBuffer(this->buffer_);
	return (true);
}

void AirSound::playSound()
{
	this->sound_.play();
}

void AirSound::pauseSound()
{
	this->sound_.pause();
}

void AirSound::stopSound()
{
	this->sound_.stop();
}

float AirSound::getVolumeSound() const
{
	return (this->sound_.getVolume());
}

void AirSound::setVolumeSound(float volume)
{
	this->sound_.setVolume(volume);
}

bool AirSound::getLoopSound() const
{
	return (this->sound_.getLoop());
}

void AirSound::setLoopSound(bool loop)
{
	this->sound_.setLoop(loop);
}

