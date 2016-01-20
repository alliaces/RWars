//
// Fichier include d'exemple pour créer une entité dans R-Wars
// Voici les étapes pour créer l'entité "foobar" qui est un monstre:
// 		1 -> copiez ce fichier "Sample.h" en "Foobar.h"
//		2 -> éditez le fichier "Foobar.h" en remplaçant les "Sample" par "Foobar"
//		3 -> remplacez le "AMother" par "AMonster"
//		Les types sont :
//			- AMonster pour les monstres
//			- ABlock pour les murs
//			- APlayer pour les joueurs
//			- AShot pour les tirs
//			- AExplosion pour les explosions
//			- ABonus pour les bonus
//		4 -> Lisez le "Sample.cpp" dans le dossier parent
//

#pragma once

#include "ASample.h"

class Sample : public AMother
{
 public:
  Sample();
  Sample(const Sample &);
  void Sample::tick(Map &map_);
  ~Sample();

 private:
#ifdef __linux__
  static Sample *instance;
#endif
};
