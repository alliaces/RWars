#ifndef ASHOT_H_
# define ASHOT_H_

# include "AEntity.h"

class AShot : public AEntity
{
public:
  AShot(int, int, int);
  AShot(const AShot &);
  AShot &operator=(const AShot &);
  ~AShot();
  int getDmg() const;
  int getOrientation() const;
  int getIdOwner() const;
  void setIdOwner(int);
  void shoot(int, int, int);
  void setDmg(int);
  virtual void tick(Map &);
   const std::string &getType() const;

protected:
  int idOwner_;
  int orientation_;
  int dmg_;
  int speed_;
};

#endif
