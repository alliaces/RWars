/*
** LinuxFileHandler.h for LinuxFileHandler.h in /home/lelong_t/rendu/CPP/CPPTeck3/tmp_cpp_spider/Includes
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Sun Nov  1 00:17:24 2015 Théophile
** Last update Sun Nov  1 00:17:25 2015 Théophile
*/

#ifndef		LINUXFILEHANDLER_H_
# define	LINUXFILEHANDLER_H_

# include <iostream>
# include <vector>
# include <string>
# include <cstdlib>
# include <dirent.h>
# include <sys/types.h>

class LinuxFileHandler
{
 public:
  LinuxFileHandler();
  ~LinuxFileHandler();
  static std::vector<std::string> getFileLib(const std::string &path, const std::string &ext);
};

#endif
