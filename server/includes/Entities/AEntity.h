#ifndef AENTITY_H_
# define AENTITY_H_

# include <vector>
# include <string>

# include "Map.h"
# include "Vector2.h"

class AEntity
{
public:
  AEntity(int, int);
  AEntity(const AEntity &);
  AEntity &operator=(const AEntity &);
  virtual ~AEntity();
  bool isTickOverride() const;
  int getId() const;
  int getIdGlobal() const;
  void setId(int);
  const Vector2 &getOldPos() const;
  const Vector2 &getPos() const;
  int getPosX() const;
  int getPosY() const;
  void setPos(const Vector2 &);
  void moveToOld();
  void move(int, int);
  const Vector2 &getSize() const;
  int getWidth() const;
  int getHeight() const;
  void setSize(const Vector2 &);
  void addSprite(int);
  const std::vector<int> &getAllSprites() const;
  int getOneSprite(int) const;
  int getCurrentSprite() const;
  bool isCreate() const;
  void create();
  bool isColliding(const AEntity &) const;
  virtual const std::string &getType() const = 0;
  virtual void tick(Map &)= 0;
  bool allowSendUpdate(int);

protected:
  int updateTimer_;
  int id_;
  int idGlobal_;
  bool isCreate_;
  int currentSprite_;
  bool tickOverride_;
  std::vector<int> sprites_;
  Vector2 pos_;
  Vector2 oldPos_;
  Vector2 size_;
  std::string type;
};

#endif
