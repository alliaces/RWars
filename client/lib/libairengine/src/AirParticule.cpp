#include "AirParticule.h"
#include <sys/time.h>
#include <iostream>

AirParticule::~AirParticule()
{
    //dtor
}

AirParticule::AirParticule(int size, sf::Color scolor, sf::Color ecolor, const Vector2f& sdir, const Vector2f& edir, int duration, const Vector2u& pos) : shape(sf::Vector2f(size, size))
{
  free_ = false;
  scolor_ = scolor;
  ecolor_ = ecolor;
  sdir_.X = sdir.X;
  sdir_.Y = sdir.Y;
  edir_.X = edir.X;
  edir_.Y = edir.Y;
  shape.setFillColor(scolor);
  shape.setPosition(pos.X, pos.Y);
  this->life = duration;
  timeval time;
  gettimeofday(&time, NULL);
  starttime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

sf::RectangleShape* AirParticule::GetShape()
{
    return (&shape);
}

bool AirParticule::Update()
{
  timeval time;
  gettimeofday(&time, NULL);
  int timep = (time.tv_sec * 1000) + (time.tv_usec / 1000);
  timep = timep - starttime;
  if (timep > life)
    return (false);
  int pcent = (((float)timep) / (float)(life)) * 100;
  sf::Color ncolor(ecolor_.r - ((ecolor_.r - scolor_.r) - ((pcent * (ecolor_.r - scolor_.r)) / 100)), \
		   ecolor_.g - ((ecolor_.g - scolor_.g) - ((pcent * (ecolor_.g - scolor_.g)) / 100)), \
		   ecolor_.b - ((ecolor_.b - scolor_.b) - ((pcent * (ecolor_.b - scolor_.b)) / 100)), \
		   ecolor_.a - ((ecolor_.a - scolor_.a) - ((pcent * (ecolor_.a - scolor_.a)) / 100)));
  shape.setFillColor(ncolor);
  sf::Vector2f nvector(edir_.X - ((edir_.X - sdir_.X) - ((pcent * (edir_.X - sdir_.X)) / 100)), \
		       edir_.Y - ((edir_.Y - sdir_.Y) - ((pcent * (edir_.Y - sdir_.Y)) / 100)));
  shape.setPosition(shape.getPosition().x + nvector.x, shape.getPosition().y + nvector.y);
  return (true);
}

bool AirParticule::free(bool set)
{
  if (set)
    free_ = true;
  return free_;
}
