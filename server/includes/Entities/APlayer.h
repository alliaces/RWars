#ifndef APLAYER_H_
# define APLAYER_H_

# include <map>
# include "AEntity.h"

class APlayer : public AEntity
{
public:
  APlayer();
  APlayer(int, int, int, int, const std::string &);
  APlayer(const APlayer &);
  APlayer &operator=(const APlayer &);
  ~APlayer();
  void init(int, int, int, int, const std::string &);
  int getDmg() const;
  void setDmg(int);
  int getSpeed() const;
  void setSpeed(int);
  void heal(int);
  int getHealth() const;
  int getMaxHealth() const;
  int getScore() const;
  void addScore(int);
  void setScore(int *);
  int getOrientation() const;
  void setOrientation(int);
  int getShoot() const;
  int getShotEntity() const;
  bool isDead() const;
  void dead();
  void refreshShoot();
  void setRefreshShoot(int);
  const std::string &getName() const;
  void takeDmg(int);
  virtual void tick(Map &);
  const std::string &getType() const;

protected:
  void up();
  void ne();
  void right();
  void se();
  void down();
  void sw();
  void left();
  void nw();
  void nope();

  int *score_;
  int shotEntity_;
  int speed_;
  int health_;
  int maxHealth_;
  bool isDead_;
  int dmg_;
  int shoot_;
  int refreshShoot_;
  int orientation_;
  std::string name_;
  std::map<int, void(APlayer::*)()> move_;
};

#endif
