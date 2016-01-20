#ifndef AMONSTER_H_
# define AMONSTER_H_

# include "AEntity.h"

class AMonster : public AEntity
{
public:
  AMonster(int, int, int, int, const std::string &);
  AMonster(const AMonster &);
  AMonster &operator=(const AMonster &);
  ~AMonster();
  int getSpawnRate() const;
  int getDmg() const;
  int getHealth() const;
  int getMaxHealth() const;
  int getShoot() const;
  int getShotEntity() const;
  void refreshShoot();
  const std::string &getName() const;
  void takeDmg(int);
  virtual void tick(Map &);
  const std::string &getType() const;

protected:
  int spawnRate_;
  int shotEntity_;
  int maxHealth_;
  int health_;
  int dmg_;
  int shoot_;
  std::string name_;
};

#endif
