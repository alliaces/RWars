#ifndef AEXPLOSION_H_
# define AEXPLOSION_H_

# include "AEntity.h"

class AExplosion : public AEntity
{
public:
  AExplosion(int, int, int);
  AExplosion(const AExplosion &);
  AExplosion &operator=(const AExplosion &);
  ~AExplosion();
  int getDmg() const;
  void setTimer();
  int getTimer() const;
  virtual void tick(Map &);
  const std::string &getType() const;

protected:
  int dmg_;
  int timer_;
};

#endif
