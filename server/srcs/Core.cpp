# include "Core.h"

Core::Core(int ac, char **av)
{
  this->ac_ = ac;
  this->av_ = av;
}

Core::~Core()
{

}

void Core::start()
{
  srand(time(NULL));
  GameManager game = GameManager();
  SNetManager net = SNetManager(&game, protocolId::TCP, this->getPort());
  game.start(&net, this->getPort(), this->getIps());
}

int Core::getPort() const
{
  int port;
  std::stringstream s(this->av_[1]);

  s >> port;
  return port;
}

const std::vector<std::string> Core::getIps() const
{
  int i = 2;

  std::vector<std::string> tmp;
  if (this->ac_ < 3)
  {
    tmp.push_back("127.0.0.1");
    return tmp;
  }
  while (i < this->ac_)
  {
    tmp.push_back(this->av_[i]);
    ++i;
  }
  return tmp;
}
