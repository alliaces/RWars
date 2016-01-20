//
// main.cpp for main.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/rtype/client/src
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Fri Dec  4 17:18:46 2015 Théophile
// Last update Wed Dec  9 18:58:34 2015 Maxime Lamarthe
//

#include "Ui.h"
#include "Network.h"
#ifndef _WIN32
#include <csignal>
#endif

int main()
{
#ifndef _WIN32
  signal(SIGPIPE,SIG_IGN);
#endif
  Ui ui;
  Network net(&ui);
  ui.setTCPListener(net.getTCPListener());
  ui.setUDPListener(net.getUDPListener());
  ui.start();
  net.start();
  ui.wait();
  net.stop();
  return (0);
}
