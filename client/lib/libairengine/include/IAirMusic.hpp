#ifndef		IAIRMUSIC_HPP_
# define	IAIRMUSIC_HPP_

#include <SFML/Audio.hpp>

class IAirMusic
{
public:
	virtual ~IAirMusic() {}
	virtual const std::string &getMusicName() const = 0;
	virtual bool openFromFile() = 0;
	virtual void playMusic() = 0;
	virtual void pauseMusic() = 0;
	virtual void stopMusic() = 0;
	virtual float getVolumeMusic() const = 0;
	virtual void setVolumeMusic(float volume) = 0;
	virtual bool getLoopMusic() const = 0;
	virtual void setLoopMusic(bool loop) = 0;
};

#endif
