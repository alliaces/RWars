#ifndef		AIRSOUND_HPP_
# define	AIRSOUND_HPP_

#include "IAirSound.hpp"

class AirSound : public IAirSound
{
public:
	AirSound(const std::string &soundName);
	~AirSound();
	bool loadSoundFromFile();
	void playSound();
	void pauseSound();
	void stopSound();
	float getVolumeSound() const;
	void setVolumeSound(float volume);
	bool getLoopSound() const;
	void setLoopSound(bool loop);
private:
	std::string soundName_;
	sf::SoundBuffer buffer_;
	sf::Sound sound_;
};

#endif
