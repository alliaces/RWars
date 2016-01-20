#include "LinuxFileHandler.h"


LinuxFileHandler::LinuxFileHandler(const std::string &fileName)
{
  this->sizeFile_ = 0;
  this->fileName_ = fileName;
  this->res_ = "";
}


LinuxFileHandler::~LinuxFileHandler()
{
}

bool LinuxFileHandler::openFile(int flags)
{
  if (flags == 0)
  {
	  if ((this->file_ = open(this->fileName_.c_str(), O_RDONLY | O_CREAT)) == -1)
		  if ((this->file_ = open(this->fileName_.c_str(), O_RDONLY)) == -1)
			  return (false);
  }
  else
  {
	  if ((this->file_ = open(this->fileName_.c_str(), O_WRONLY | O_CREAT | O_EXCL,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		  if ((this->file_ = open(this->fileName_.c_str(), O_WRONLY | O_TRUNC)) == -1)
			  return (false);
  }
  return (true);
}

const std::string &LinuxFileHandler::readFile(int size)
{
  ssize_t nbRead(0);
  char buf[size];

  this->res_ = "";
  if ((nbRead = read(this->file_, buf, (size_t) size)) == -1)
    return (this->res_);
  if (nbRead != size)
    return (this->res_);
  buf[nbRead] = '\0';
  this->res_ = buf;
  return (this->res_);
}

bool LinuxFileHandler::writeFile(const std::string &str)
{
  ssize_t nbRead(0);

  if ((nbRead = write(this->file_, str.c_str(), str.size())) == -1)
  {
    close(this->file_);
    return (false);
  }
  if (nbRead != (ssize_t) str.size())
  {
    close(this->file_);
    return (false);
  }
  return (true);
}

int LinuxFileHandler::getFileSize()
{
  struct stat statbuf;

  if (stat(this->fileName_.c_str(), &statbuf) == -1)
    return (0);
  this->sizeFile_ = statbuf.st_size;
  return (this->sizeFile_);
}

bool LinuxFileHandler::closeFile()
{
  if (close(this->file_) == -1)
    return (false);
  return (true);
}

bool LinuxFileHandler::deleteFile()
{
  if (remove(this->fileName_.c_str()) != 0)
    return (false);
  return (true);
}
