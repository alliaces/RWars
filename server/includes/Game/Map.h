#ifndef MAP_H_
# define MAP_H_

# include <vector>

class EntityContainer;
class AEntity;

class Map : public std::vector<AEntity *>
{
public:
  Map();
  ~Map();
  void start(void *, int *);
  void *createEntity(int);
private:
  EntityContainer *container_;
  int *currentId_;
};

#endif
