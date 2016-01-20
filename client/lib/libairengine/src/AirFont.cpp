#include "AirFont.h"

AirFont::AirFont(const std::string& path)
{
    _font.loadFromFile(path);
}

const sf::Font& AirFont::GetFont()
{
    return (_font);
}


AirFont::~AirFont()
{
    //dtor
}
