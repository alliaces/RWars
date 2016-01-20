#pragma once
#include "AFileHandler.h"
#include <vector>

class WindowsFileHandler : public AFileHandler
{
public:
	WindowsFileHandler(const std::string &fileName);
	~WindowsFileHandler();
	static std::vector<std::string> getFileLib(const std::string &path);
  bool openFile(int flags);
	bool writeFile(const std::string &str);
	const std::string &readFile(int size);
	int getFileSize();
	bool closeFile();
	bool deleteFile();
private:
  std::string fileName_;
	std::string dataRead_;
	HANDLE fileMod_;
	DWORD sizeFile_;
};
