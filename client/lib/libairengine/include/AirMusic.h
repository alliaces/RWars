#ifndef		AIRMUSIC_HPP_
# define	AIRMUSIC_HPP_

#include "IAirMusic.hpp"

class AirMusic : public IAirMusic
{
public:
	AirMusic(const std::string &musicName);
	~AirMusic();
	const std::string &getMusicName() const;
	bool openFromFile();
	void playMusic();
	void pauseMusic();
	void stopMusic();
	float getVolumeMusic() const;
	void setVolumeMusic(float volume);
	bool getLoopMusic() const;
	void setLoopMusic(bool loop);
private:
	std::string musicName_;
	sf::Music music_;
};

#endif
