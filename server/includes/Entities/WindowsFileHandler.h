#pragma once
#include <windows.h>
#include <vector>
#include <string>

class WindowsFileHandler
{
public:
	WindowsFileHandler();
	~WindowsFileHandler();
	static std::vector<std::string> getFileLib(const std::string &path, const std::string &ext);
};
