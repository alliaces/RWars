#ifndef AIRPARTICULEGENERATOR_H
#define AIRPARTICULEGENERATOR_H

#include "Vector2f.h"
#include "Vector2u.h"
#include "AirParticule.h"
#include <SFML/Graphics.hpp>
#include <vector>

class AirParticuleGenerator
{
 public:
  AirParticuleGenerator(Vector2f sdir, float psdir, Vector2f edir, float pedir, sf::Color scolor, int pscolor, sf::Color ecolor, int pecolor, int size, int psize, int life, int plife, int nbpersec, Vector2u pos, int ppos);
  virtual ~AirParticuleGenerator();
  void Update();
  const std::vector<AirParticule*>& GetAllShape();
  void setPosition(Vector2u pos);
 protected:
 private:
  void createParticule();
  std::vector<AirParticule*> shapes;
  Vector2f sdir_;
  float psdir_;
  Vector2f edir_;
  float pedir_;  
  sf::Color scolor_;
  sf::Color ecolor_;
  int pscolor_;
  int pecolor_;
  int size_;
  int psize_;
  int nbpersec_;
  Vector2u pos_;
  int ppos_;
  int life_;
  int plife_;
  int time;
};

#endif // AIRSPRITE_H
