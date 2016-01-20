#include "WindowsFileHandler.h"

WindowsFileHandler::WindowsFileHandler(const std::string &fileName)
{
	this->dataRead_ = "";
	this->fileName_ = fileName;
}


WindowsFileHandler::~WindowsFileHandler()
{
}

std::vector<std::string> WindowsFileHandler::getFileLib(const std::string &path)
{
	std::vector<std::string> filesLib;
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	if ((hFind = FindFirstFile(path.c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
	{
		do {
			filesLib.push_back(FindFileData.cFileName);
			} while(FindNextFile(hFind, &FindFileData));
			FindClose(hFind);
	}
	return (filesLib);
}

bool WindowsFileHandler::openFile(int flags)
{
	if (flags == 0)
	{
		if ((this->fileMod_ = CreateFile(this->fileName_.c_str(), GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
				return (false);
	}
	else
	{
		if ((this->fileMod_ = CreateFile(this->fileName_.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE,
			NULL, CREATE_NEW | TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
			return (false);
	}
	return (true);
}

const std::string &WindowsFileHandler::readFile(int size)
{
	char *readBuffer = new char[size];
	DWORD  dwBytesRead = 0;

	if (ReadFile(this->fileMod_, readBuffer, (DWORD) size, &dwBytesRead, NULL) == FALSE)
		return (this->dataRead_);
	readBuffer[dwBytesRead] = '\0';
	this->dataRead_ = readBuffer;
	return (this->dataRead_);
}

bool WindowsFileHandler::writeFile(const std::string &str)
{
	DWORD dwBytesToWrite((DWORD)strlen(str.c_str()));
	DWORD dwBytesWritten(0);

	if (WriteFile(this->fileMod_, str.c_str(), dwBytesToWrite, &dwBytesWritten, NULL) == FALSE)
		return (false);
	else
	{
		if (dwBytesWritten != dwBytesToWrite)
			return (false);
	}
	return (true);
}

int WindowsFileHandler::getFileSize()
{
	HANDLE hFile = CreateFile(this->fileName_.c_str(), 0,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE)
		this->sizeFile_ = GetFileSize(hFile, NULL);
	return ((int) this->sizeFile_);
}

bool WindowsFileHandler::closeFile()
{
	return ((bool) CloseHandle(this->fileMod_));
}

bool WindowsFileHandler::deleteFile()
{
	if (DeleteFile(this->fileName_.c_str()) == FALSE)
		return (false);
	return (true);
}
