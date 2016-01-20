#include "UtilsSplit.h"

UtilsSplit::UtilsSplit()
{
}


UtilsSplit::~UtilsSplit()
{
}

/// This function while split string with delimiter
/// return substring into a std::vector<std::string>

std::vector<std::string> &UtilsSplit::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> UtilsSplit::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::vector<std::string> UtilsSplit::split(const std::string &s, const std::string &delim) {
	std::vector<std::string> elems;
	std::string tmp(s);
	size_t foundPreview = 0;
	size_t found = s.find(delim, foundPreview);

	elems.push_back(tmp.substr(0, found));
	foundPreview = found + 1;
	while ((found = s.find(delim, foundPreview)) != std::string::npos)
	{
		elems.push_back(tmp.substr(foundPreview + delim.size() - 1,
			found - foundPreview - delim.size() + 1));
		foundPreview = found + 1;
	}
	elems.push_back(tmp.substr(foundPreview + delim.size() - 1,
		found - foundPreview - delim.size() + 1));
	return elems;
}
