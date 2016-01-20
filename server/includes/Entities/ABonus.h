#ifndef ABONUS_H_
# define ABONUS_H_

# include "AEntity.h"

class ABonus : public AEntity
{
public:
  ABonus(int, int);
  ABonus(const ABonus &);
  ABonus &operator=(const ABonus &);
  ~ABonus();
  virtual void tick(Map &);
  const std::string &getType() const;
  virtual void collideBonus(AEntity *);
  int getSpawnRate() const;

protected:
  int spawnRate_;
};

#endif
