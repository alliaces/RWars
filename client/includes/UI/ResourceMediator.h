/*
** ResourceMediator.h for ResourceMediator.h in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/include
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Fri Dec  4 17:32:46 2015 Théophile
** Last update Fri Dec  4 17:45:16 2015 Théophile
*/

#ifndef		RESOURCEMEDIATOR_H_
# define	RESOURCEMEDIATOR_H_

#include <AirEngine.h>
#include <map>

class ResourceMediator
{
public:
	ResourceMediator();
	~ResourceMediator();
	AirPicture *getPictureById(int id);
	AirFont *getFontById(int id);
	IAirMusic *getMusicById(int id);
	IAirSound *getSoundById(int id);
private:
	std::map<int, AirFont*> fonts_;
	std::map<int, AirPicture*> resources_;
	std::map<int, IAirMusic*> musics_;
	std::map<int, IAirSound*> sounds_;
};

#endif
