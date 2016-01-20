#ifndef AIRPARTICULE_H
#define AIRPARTICULE_H

#include "IEntity.h"
#include "Vector2f.h"
#include "Vector2u.h"
#include <SFML/Graphics.hpp>
#include <mutex>

class AirParticule
{
 public:
  AirParticule(int size, sf::Color scolor, sf::Color ecolor, const Vector2f& sdir,  const Vector2f& edir, int duration, const Vector2u& pos);
  virtual ~AirParticule();
  bool Update();
  sf::RectangleShape* GetShape();
  bool free(bool set);
 protected:
 private:
  sf::RectangleShape shape;
  int life;
  int starttime;
  sf::Color scolor_;
  sf::Color ecolor_;
  Vector2f sdir_;
  Vector2f edir_;
  bool free_;
};

#endif // AIRSPRITE_H
