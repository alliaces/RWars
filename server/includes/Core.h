#ifndef CORE_H_
# define CORE_H_

# include <cstdlib>

# include "GameManager.h"
# include "Protocol.h"

class Core
{
public:
  Core(int, char **);
  ~Core();
  void start();

private:
  const std::vector<std::string> getIps() const;
  int getPort() const;

  int ac_;
  char **av_;
};

#endif
