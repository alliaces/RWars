/*
** AFileHandler.h for AFileHandler.h in /home/lelong_t/rendu/CPP/CPPTeck3/tmp_cpp_spider/Includes
**
** Made by Théophile
** Login   <lelong_t@epitech.net>
**
** Started on  Sat Oct 31 23:58:19 2015 Théophile
** Last update Sat Oct 31 23:58:25 2015 Théophile
*/

#ifndef		AFILEHANDLER_H_
# define	AFILEHANDLER_H_

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

class AFileHandler
{
 public:
  virtual ~AFileHandler()
    {
    }

  virtual bool openFile(int flags) = 0;
  virtual const std::string &readFile(int size) = 0;
  virtual bool writeFile(const std::string &str) = 0;
  virtual int getFileSize() = 0;
  virtual bool closeFile() = 0;
  virtual bool deleteFile() = 0;
};

#endif
