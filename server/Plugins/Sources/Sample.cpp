//
// Fichier source d'exemple pour créer une entité dans R-Wars
// Voici les étapes pour créer l'entité "foobar" qui est un monstre:
//		1 -> La suite est à faire, si le fichier include "Foobar.h" a été réalisé
//			 suivant les consignes du fichier "Sample.h"
// 		2 -> Copiez ce fichier "Sample.cpp" en "Foobar.cpp"
//		3 -> Éditez le fichier "Foobar.cpp" en remplaçant les "Sample" par "Foobar"
//		4 -> Remplacez le "AMother" par "AMonster"
//		5 -> Mettre les arguments à AMonster selon votre choix

//		Les arguments des entités sont :
//
//			pour un mur :
//			- ABlock(la vie du block (nombre entier positif), 
//					 si le block est destructible ou non (true(vrai)/false(faux)),
//					 la largeur (entier positif),
//					 la hauteur (entier positif))
//
//			pour un bonus :
//			- ABonus(la largeur (entier positif),
//					 la hauteur (entier positif))
//	
//			pour une explosion :
//			- AExplosion(la quantité de dommages qu'il inflige (entier positif),
//						 la largeur (entier positif),
//						 la hauteur (entier positif))
//
//			pour un monstre :
//			- AMonster(la vie du monstre (nombre entier positif),
//					   la quantité de dommages qu'il inflige (entier positif),
//					   la largeur (entier positif),
//					   la hauteur (entier positif),
//					   son nom (chaine de caractère entre ""))
//			   
//			pour un joueur :
//			- APlayer(la vie du joueur (nombre entier positif),
//					  la quantité de dommages qu'il inflige (entier positif),
//					  la largeur (entier positif),
//			  		  la hauteur (entier positif),
//					  son nom (chaine de caractère entre ""))
//
//			pour un tir :			   
//			- AShot(la vitesse du tir (nombre entier positif),
//					la largeur (entier positif),
//					la hauteur (entier positif))
//
//		6 -> Remplacez l'argument de addSprite par le nombre que vous entré dans le
//			 "config.cfg" du client
//		7 -> Vous pouvez maintenant compilez en exécutant le script "make_all.sh"
//			 dans le dossier Plugins
//		8 -> Jouez !			
//
//
//		P.S. : Pour les utilisateurs avancés, vous pouvez modifier le comportement
//			   de votre extension en modifiant la fonction void Sample::tick(Map &map_)
//			   et pour les Bonus vous pouvez modifier le comportement en modifiant
//			   la fonction void Sample::collideBonus(AEntity *entity)
//

#include "Sample.h"

#ifdef __linux__
Sample	*Sample::instance; 
#endif


Sample::Sample() : AMother(/*x, y, z, ...*/)
{
	this->addSprite(/*a*/);
}

Sample::Sample(const Sample &other) : ASample(other)
{}

void Sample::tick(Map &map_)
{}

Sample::~Sample()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Sample());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Sample());
	}
}
#endif