#include "Core.h"

int main(int ac, char **av)
{
  if (ac == 1)
    {
      std::cout << "Usage: " << av[0] << " port [[ip], ...]]" << std::endl;
      return -1;
    }
  Core rtype = Core(ac, av);
  rtype.start();
  return 0;
}
