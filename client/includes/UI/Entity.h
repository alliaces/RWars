#ifndef         ENTITY_H_
# define        ENTITY_H_

#include <AirEngine.h>
#include "ResourceMediator.h"

class Entity
{
 public:
  Entity(AScene *scene, ResourceMediator *res, int id, int x, int y, int rot, int scale_x, int scale_y, int spriteid, std::string name);
  ~Entity();
  void Update(int id, int x, int y, int rot, int spriteid);
  bool checkUpdate();
  void Destroy();
  int getId();
 private:
  unsigned int time_;
  ResourceMediator *res_;
  AScene* scene;
  int id;
  int scale_x;
  int scale_y;
  AirSprite *sprite_;
  AirTextBox *text_;
};

#endif
