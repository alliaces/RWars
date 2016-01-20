//
// LinuxFileHandler.cpp for LinuxFileHandler.cpp in /home/lelong_t/rendu/CPP/CPPTeck3/tmp_cpp_spider/Sources
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Sun Nov  1 00:16:45 2015 Théophile
// Last update Sun Nov  1 00:16:52 2015 Théophile
//

#include "LinuxFileHandler.h"


LinuxFileHandler::LinuxFileHandler()
{
}


LinuxFileHandler::~LinuxFileHandler()
{
}

std::vector<std::string> LinuxFileHandler::getFileLib(const std::string &path,
		  const std::string &ext)
{
	std::vector<std::string> listLibs;
	DIR * direct;
	char * dir_name = (char *)path.c_str();

	if (!(direct = opendir(dir_name)))
		return (listLibs);
	while (1)
	{
		struct dirent * entry;
		std::string tmpName;
		std::string tmpExt;
		size_t found;

		if (!(entry = readdir(direct)))
			break;
		tmpName = entry->d_name;
		tmpExt = entry->d_name;
		if ((found = tmpName.find('.')) != std::string::npos)
		  {
		    tmpExt.erase(0, found + 1);
		    if (tmpExt == ext)
		      listLibs.push_back(path + tmpName);
		  }
		else
		  break;
	}
	if (closedir(direct))
		return (listLibs);
	return (listLibs);
}
