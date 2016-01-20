#include "EntityManager.h"
#include "APlayer.h"
#include "AExplosion.h"
#include "AMonster.h"
#include "ABlock.h"
#include "AShot.h"
#include "ABonus.h"

EntityManager::EntityManager()
{
  std::vector<std::pair<AEntity *, LOADER>> player;
  std::vector<std::pair<AEntity *, LOADER>> block;
  std::vector<std::pair<AEntity *, LOADER>> shot;
  std::vector<std::pair<AEntity *, LOADER>> monster;
  std::vector<std::pair<AEntity *, LOADER>> explosion;
  std::vector<std::pair<AEntity *, LOADER>> bonus;
  
  checkEntity_.insert(std::pair<std::string, checkEntity>("Player", &EntityManager::checkPlayer));
  checkEntity_.insert(std::pair<std::string, checkEntity>("Monster", &EntityManager::checkMonster));
  checkEntity_.insert(std::pair<std::string, checkEntity>("Shot", &EntityManager::checkShot));
  checkEntity_.insert(std::pair<std::string, checkEntity>("Block", &EntityManager::checkBlock));
  checkEntity_.insert(std::pair<std::string, checkEntity>("Explosion", &EntityManager::checkExplosion));
  checkEntity_.insert(std::pair<std::string, checkEntity>("Bonus", &EntityManager::checkBonus));
  
  entities_.insert(std::pair<std::string, std::vector<std::pair<AEntity *, LOADER>>>("Player", player));
  entities_.insert(std::pair<std::string, std::vector<std::pair<AEntity *, LOADER>>>("Block", block));
  entities_.insert(std::pair<std::string, std::vector<std::pair<AEntity *, LOADER>>>("Shot", shot));
  entities_.insert(std::pair<std::string, std::vector<std::pair<AEntity *, LOADER>>>("Monster", monster));
  entities_.insert(std::pair<std::string, std::vector<std::pair<AEntity *, LOADER>>>("Explosion", explosion));
  entities_.insert(std::pair<std::string, std::vector<std::pair<AEntity *, LOADER>>>("Bonus", bonus));
}

EntityManager::~EntityManager()
{
	for (std::pair<std::string, std::vector<std::pair<AEntity *, LOADER>>> pair : this->entities_)
	{
		for (std::pair<AEntity *, LOADER> entity : pair.second)
		{
			delete (entity.first);
			entity.second->close();
			delete (entity.second);
		}
	}
}

void EntityManager::checkPlugin()
{
  std::cout << "CHECK PLUGIN" << std::endl;
#ifdef _WIN32
  this->pathLib_ = WindowsFileHandler::getFileLib("./Plugins/Win32/", "dll");
#elif __linux__
  this->pathLib_ = LinuxFileHandler::getFileLib("./Plugins/Linux/", "so");
#endif
  for (std::vector<std::string>::iterator lib = pathLib_.begin() ; lib != pathLib_.end(); ++lib)
    {
		try
		{
			if (std::find(currentDllpath_.begin(), currentDllpath_.end(), *lib) == currentDllpath_.end())
			{
				#ifdef _WIN32
					WLoad<AEntity> *Loader = new WLoad<AEntity>();
				#elif __linux__
					ULoad<AEntity> *Loader = new ULoad<AEntity>();
				#endif
				actual_ = Loader->load(lib->c_str());
				auto find = checkEntity_.find(actual_->getType());
				checkEntity fct = find->second;
				if (find != checkEntity_.end() && (this->*fct)())
				{
					currentDllpath_.push_back(*lib);
					std::cout << *lib << " loaded" << std::endl;
					auto it = this->entities_.find(actual_->getType());
					std::pair<AEntity *, LOADER> tmp(actual_, Loader);
					it->second.push_back(tmp);
				}
				else
				{
					std::cerr << *lib << " incorrect" << std::endl;
					delete (actual_);
					Loader->close();
					delete (Loader);
				}
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
    }
}

bool EntityManager::checkPlayer() const
{
	bool ret = true;
	ret &= checkSize(this->actual_->getSize().x, this->actual_->getSize().y);
	ret &= checkNeg(static_cast<APlayer *>(actual_)->getHealth());
	ret &= checkNeg(static_cast<APlayer *>(actual_)->getDmg());
	return ret;
}

bool EntityManager::checkMonster() const
{
	bool ret = true;
	ret &= checkSize(this->actual_->getSize().x, this->actual_->getSize().y);
	ret &= checkNeg(static_cast<AMonster *>(actual_)->getHealth());
	ret &= checkNeg(static_cast<AMonster *>(actual_)->getDmg());
	return ret;
}

bool EntityManager::checkBonus() const
{
	bool ret = true;
	ret &= checkSize(this->actual_->getSize().x, this->actual_->getSize().y);
	return ret;
}

bool EntityManager::checkBlock() const
{
	bool ret = true;
	ret &= checkSize(this->actual_->getSize().x, this->actual_->getSize().y);
	ret &= checkNeg(static_cast<ABlock *>(actual_)->getHealth());
	return ret;
}

bool EntityManager::checkShot() const
{
	bool ret = true;
	ret &= checkSize(this->actual_->getSize().x, this->actual_->getSize().y);
	ret &= checkNeg(static_cast<AShot *>(actual_)->getDmg());
	return ret;
}

bool EntityManager::checkExplosion() const
{
	bool ret = true;
	ret &= checkSize(this->actual_->getSize().x, this->actual_->getSize().y);
	ret &= checkNeg(static_cast<AExplosion *>(actual_)->getDmg());
	return ret;
}

bool EntityManager::checkNeg(int nb) const
{
	if (nb < 0)
		return false;
	return true;
}

bool EntityManager::checkSize(int width, int height) const
{
	if (width < 1)
		return false;	
	if (height < 1)
		return false;
	return true;
}

const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> EntityManager::getAllEntities() const
{
  return this->entities_;
}

const std::vector<std::pair<AEntity *, LOADER>> &EntityManager::getPlayers() const
{
  return this->entities_.find("Player")->second;
}

const std::vector<std::pair<AEntity *, LOADER>> &EntityManager::getBlocks() const
{
  return this->entities_.find("Block")->second;
}

const std::vector<std::pair<AEntity *, LOADER>> &EntityManager::getShots() const
{
  return this->entities_.find("Shot")->second;
}

const std::vector<std::pair<AEntity *, LOADER>> &EntityManager::getMonsters() const
{
  return this->entities_.find("Monster")->second;
}

const std::vector<std::pair<AEntity *, LOADER>> &EntityManager::getExplosions() const
{
  return this->entities_.find("Explosion")->second;
}

const std::vector<std::pair<AEntity *, LOADER>> &EntityManager::getBonus() const
{
  return this->entities_.find("Bonus")->second;
}
