#include "Entity.h"

Entity::Entity(AScene *scene, ResourceMediator *res, int id, int x, int y, int rot, int scale_x, int scale_y, int spriteid, std::string name)
{
  time_ = time(NULL);
  res_ = res;
  this->scene = scene;
  this->id = id;
  (void)rot;
  (void)name;
  this->scale_x = scale_x;
  this->scale_y = scale_y;
  sprite_ = new AirSprite(res->getPictureById(spriteid), Vector2u(x, y), Vector2u(scale_x, scale_y));
  scene->AddEntity(sprite_);
}

Entity::~Entity()
{

}

void Entity::Update(int id, int x, int y, int rot, int spriteid)
{
  (void)id;
  (void)rot;
  time_ = time(NULL);
  sprite_->SetPicture(res_->getPictureById(spriteid));
  sprite_->SetPos(Vector2u(x, y));
}

bool Entity::checkUpdate()
{
  if (time(NULL) - time_ > 1)
    {
      scene->RemoveEntity(sprite_);
      return (false);
    }
  return (true);
}

int Entity::getId()
{
  return (id);
}

void Entity::Destroy()
{
  scene->RemoveEntity(sprite_);
}
