#ifndef ABLOCK_H_
# define ABLOCK_H_

# include "AEntity.h"

class ABlock : public AEntity
{

public:
  ABlock(int, bool, int, int);
  ABlock(const ABlock &);
  ABlock &operator=(const ABlock &);
  ~ABlock();
  int getHealth() const;
  void takeDmg(int);
  virtual void tick(Map &);
  const std::string &getType() const;
  bool isCollidable() const;

protected:
  bool isDestructible_;
  bool isCollidable_;
  int health_;
};

#endif
