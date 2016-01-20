#ifndef ITICK_H_
# define TICK_H_

class ITick
{
public:
  virtual ~ITick() {}
  virtual void tick(std::vector<AEntity *> &) = 0;
};

#endif
