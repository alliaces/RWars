#ifndef ENTITYCONTAINER_H_
# define ENTITYCONTAINER_H_

# include "AEntity.h"
# include "APlayer.h"
# include "AShot.h"
# include "AMonster.h"
# include "ABlock.h"
# include "AExplosion.h"
# include "ABonus.h"

# ifdef _WIN32
#  include "WinLoad.h"
#  define LOADER WLoad<AEntity> *
# elif __linux__
#  include "UnixLoad.h"
#  define LOADER ULoad<AEntity> *
# endif

class EntityContainer
{
public:
  EntityContainer(const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> &);
  ~EntityContainer();
  AEntity *getOneEntity(int) const;
  AEntity *getOnePlayer() const;
  AEntity *getOneBlock() const;
  AEntity *getOneShot() const;
  AEntity *getOneMonster() const;
  AEntity *getOneExplosion() const;
  AEntity *getOneBonus() const;

private:
  std::vector<std::pair<AEntity *, LOADER>> players_;
  std::vector<std::pair<AEntity *, LOADER>> blocks_;
  std::vector<std::pair<AEntity *, LOADER>> shots_;
  std::vector<std::pair<AEntity *, LOADER>> monsters_;
  std::vector<std::pair<AEntity *, LOADER>> explosions_;
  std::vector<std::pair<AEntity *, LOADER>> bonus_;
};

#endif
