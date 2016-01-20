#ifndef         PLAYER_H_
# define        PLAYER_H_

#include <AirEngine.h>
#include "ResourceMediator.h"
#include "Utils.h"

class Player
{
 public:
  Player(AScene *scene, ResourceMediator *res, int id, int x, int y, int rot, int scale_x, int scale_y, int spriteid, std::string name);
  void Update(int id, int x, int y, int rot, int spriteid);
  bool checkUpdate();
  void Destroy();
  int getId();
  ~Player();
 private:
  unsigned int time_;
  ResourceMediator *res_;
  AScene* scene;
  int id;
  int scale_x;
  int scale_y;
  AirSprite *sprite_;
  AirText *text_;
  AirParticuleGenerator *part_;
};

#endif
