#include "WindowsFileHandler.h"

WindowsFileHandler::WindowsFileHandler()
{
}


WindowsFileHandler::~WindowsFileHandler()
{
}

std::vector<std::string> WindowsFileHandler::getFileLib(const std::string &path, const std::string &ext)
{
	std::string lib(path + "/*." + ext);
	std::vector<std::string> filesLib;
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	
	if ((hFind = FindFirstFile(lib.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			filesLib.push_back(path + FindFileData.cFileName);
			} while(FindNextFile(hFind, &FindFileData));
			FindClose(hFind);
	}
	return (filesLib);
}
