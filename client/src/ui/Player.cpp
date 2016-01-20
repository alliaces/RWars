#include "Player.h"

Player::Player(AScene *scene, ResourceMediator *res, int id, int x, int y, int rot, int scale_x, int scale_y, int spriteid, std::string name)
{
  res_ = res;
  this->id = id;
  this->scene = scene;
  (void)rot;
  (void)name;
  time_ = time(NULL);
  this->scale_x = scale_x;
  this->scale_y = scale_y;
  sf::Color color;
  if (id == 0)
    color = sf::Color::Blue;
  else if (id == 1)
    color = sf::Color::Red;
  else if (id == 2)
    color = sf::Color::Yellow;
  else
    color = sf::Color::Green;  
  text_ = new AirText(res->getFontById(0), "P" + Utils::to_string(id + 1), Vector2u(x + scale_x / 2, y - scale_y / 2), color, 10);
  sprite_ = new AirSprite(res->getPictureById(spriteid), Vector2u(x, y), Vector2u(scale_x, scale_y));
  part_ = new AirParticuleGenerator(Vector2f(-3, 0), 1, // vector start
										  Vector2f(-3, 0), 0.8, // vector end
										  color, 0,
				    sf::Color(255,255, 0, 0), 0, 1 * (scale_y / 30), 2, // size
				    100 * (scale_y / 5), 0, // life
										  100, // nb particules per secs
										  Vector2u(x, y + scale_y / 2),
										  0);
  scene->AddEntity(text_);
  scene->AddEntity(sprite_);
  scene->AddParticules(part_);
}

Player::~Player()
{

}

void Player::Update(int id, int x, int y, int rot, int spriteid)
{
  (void)id;
  (void)rot;
  time_ = time(NULL);
  sprite_->SetPicture(res_->getPictureById(spriteid));
  text_->setPosition(Vector2u(x + scale_x / 2, y - scale_y / 2));
  sprite_->SetPos(Vector2u(x, y));
  part_->setPosition(Vector2u(x, y + scale_y / 2));
}

bool Player::checkUpdate()
{
  if (time(NULL) - time_ > 1)
    {
      scene->RemoveEntity(sprite_);
      scene->RemoveEntity(text_);
      scene->RemoveParticules(part_);
      return (false);
    }
  return (true);
}

int Player::getId()
{
  return (id);
}

void Player::Destroy()
{
  scene->RemoveEntity(text_);
  scene->RemoveEntity(sprite_);
  scene->RemoveParticules(part_);
}
