#ifndef ENTITYMANAGER_H_
# define ENTITYMANAGER_H_

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <map>
# include "AEntity.h"

# ifdef _WIN32
#   include "WinLoad.h"
#define LOADER WLoad<AEntity> *
#   include "WindowsFileHandler.h"
# elif __linux__
#   include "UnixLoad.h"
#define LOADER ULoad<AEntity> *
#   include "LinuxFileHandler.h"
# endif

class EntityManager
{
public:
  EntityManager();
  ~EntityManager();
  void checkPlugin();
  const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> getAllEntities() const;
  const std::vector<std::pair<AEntity *, LOADER>> &getPlayers() const;
  const std::vector<std::pair<AEntity *, LOADER>> &getBlocks() const;
  const std::vector<std::pair<AEntity *, LOADER>> &getShots() const;
  const std::vector<std::pair<AEntity *, LOADER>> &getMonsters() const;
  const std::vector<std::pair<AEntity *, LOADER>> &getExplosions() const;
  const std::vector<std::pair<AEntity *, LOADER>> &getBonus() const;

private:
  typedef bool (EntityManager::*checkEntity)(void) const;
  bool checkPlayer() const;
  bool checkMonster() const;
  bool checkBonus() const;
  bool checkBlock() const;
  bool checkShot() const;
  bool checkExplosion() const;
  bool checkSize(int witdh, int height) const;
  bool checkNeg(int nb) const;

  std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> entities_;
  std::map<std::string, checkEntity> checkEntity_;
  std::vector<std::string> pathLib_;
  std::vector<std::string> currentDllpath_;
  AEntity *actual_;
};

#endif
