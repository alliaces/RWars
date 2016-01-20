#ifndef GAMEBUILDER_H_
# define GAMEBUILDER_H_

# include "Game.h"

class GameBuilder
{
public:
  GameBuilder(const std::vector<std::string> &, int);
  ~GameBuilder();
  Game *createGame(const std::string &, const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> &, unsigned int);
  Game *createGame(const std::string &, const std::map<std::string, std::vector<std::pair<AEntity *, LOADER>>> &);

private:
  std::vector<std::string> ips_;
  int port_;
  unsigned int currentIp_;
};

#endif
