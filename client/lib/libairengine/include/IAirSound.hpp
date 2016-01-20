#ifndef		IAIRSOUND_HPP_
# define	IAIRSOUND_HPP_

#include <SFML/Audio.hpp>

class IAirSound
{
public:
	virtual ~IAirSound() {}
	virtual bool loadSoundFromFile() = 0;
	virtual void playSound() = 0;
	virtual void pauseSound() = 0;
	virtual void stopSound() = 0;
	virtual float getVolumeSound() const = 0;
	virtual void setVolumeSound(float volume) = 0;
	virtual bool getLoopSound() const = 0;
	virtual void setLoopSound(bool loop) = 0;
};

#endif
