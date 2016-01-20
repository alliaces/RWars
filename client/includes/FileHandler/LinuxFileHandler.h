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

#include "AFileHandler.h"

class LinuxFileHandler : public AFileHandler
{
 public:
  LinuxFileHandler(const std::string &fileName);
  ~LinuxFileHandler();
  bool openFile(int flags);
  bool writeFile(const std::string &str);
  const std::string &readFile(int size);
  int getFileSize();
  bool closeFile();
  bool deleteFile();
 private:
  int file_;
  int sizeFile_;
  std::string fileName_;
  std::string res_;
};

#endif
