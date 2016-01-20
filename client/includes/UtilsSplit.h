#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class UtilsSplit
{
public:
	UtilsSplit();
	~UtilsSplit();

	static std::vector<std::string> split(const std::string &s, char delim);
	static std::vector<std::string> split(const std::string &s, const std::string &delim);

private:
	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
};

