#include "AirParticuleGenerator.h"
#include <sys/time.h>
#include <iostream>

AirParticuleGenerator::~AirParticuleGenerator()
{
}

AirParticuleGenerator::AirParticuleGenerator(Vector2f edir, float pedir, Vector2f sdir, float psdir, sf::Color scolor, int pscolor, sf::Color ecolor, int pecolor, int size, int psize, int life, int plife, int nbpersec, Vector2u pos, int ppos)
{
  std::srand(std::time(0));
  sdir_.X = sdir.X;
  sdir_.Y = sdir.Y;
  psdir_ = psdir;
  edir_.X = edir.X;
  edir_.Y = edir.Y;
  pedir_ = pedir;  
  scolor_ = scolor;
  ecolor_ = ecolor;
  pscolor_ = pscolor;
  pecolor_ = pecolor;
  size_ = size;
  psize_ = psize;
  nbpersec_ = nbpersec;
  pos_.X = pos.X;
  pos_.Y = pos.Y;
  ppos_ = ppos;
  life_ = life;
  plife_ = plife;
  timeval times;
  gettimeofday(&times, NULL);
  time = (times.tv_sec * 1000) + (times.tv_usec / 1000);
}

const std::vector<AirParticule*>& AirParticuleGenerator::GetAllShape()
{
    return (shapes);
}

void AirParticuleGenerator::setPosition(Vector2u pos)
{
  pos_.X = pos.X;
  pos_.Y = pos.Y;
}

void AirParticuleGenerator::Update()
{
  timeval times;
  gettimeofday(&times, NULL);
  int temp = ((times.tv_sec * 1000) + (times.tv_usec / 1000)) - time;
  int nbtobuild = (((float)nbpersec_ * (float)temp) / (float)1000);
  for (int i = 0; i < (nbtobuild > nbpersec_ ? nbpersec_ : nbtobuild); ++i)
    createParticule();
  time += (((float)nbtobuild * (float)1000) / (float)nbpersec_);
  for (unsigned int i = 0; i < shapes.size(); ++i)
    {
      if (!shapes[i]->Update())
	{
	  AirParticule* par = shapes[i];
	  shapes.erase(shapes.begin() + i);
	  delete(par);
	}
    }
}

double fRand(double fMin, double fMax)
{
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

void AirParticuleGenerator::createParticule()
{
  int size = (fRand((size_ - psize_), (size_ + psize_)));
  sf::Color scolor(fRand((scolor_.r - pscolor_), (scolor_.r + pscolor_)), \
		   fRand((scolor_.g - pscolor_), (scolor_.g + pscolor_)), \
		   fRand((scolor_.b - pscolor_), (scolor_.b + pscolor_)), \
		   fRand((scolor_.a - pscolor_), (scolor_.a + pscolor_)));
  sf::Color ecolor(fRand((ecolor_.r - pecolor_), (ecolor_.r + pecolor_)), \
		   fRand((ecolor_.g - pecolor_), (ecolor_.g + pecolor_)), \
		   fRand((ecolor_.b - pecolor_), (ecolor_.b + pecolor_)), \
		   fRand((ecolor_.a - pecolor_), (ecolor_.a + pecolor_)));
  Vector2f sdir(fRand((sdir_.X - psdir_), (sdir_.X + psdir_)), \
		fRand((sdir_.Y - psdir_), (sdir_.Y + psdir_)));
  Vector2f edir(fRand((edir_.X - pedir_), (edir_.X + pedir_)), \
		fRand((edir_.Y - pedir_), (edir_.Y + pedir_)));
  int life = (fRand((life_ - plife_), (life_ + plife_)));
  Vector2u pos(fRand((pos_.X - ppos_), (pos_.X + ppos_)),							\
	       fRand((pos_.Y - ppos_), (pos_.Y + ppos_)));  
  shapes.push_back(new AirParticule(size, scolor, ecolor, sdir, edir, life, pos));
}
