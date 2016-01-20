#include "AirPicture.h"

AirPicture::AirPicture(const std::string& path)
{
    _texture.loadFromFile(path);
}

AirPicture::~AirPicture()
{
    //dtor
}

sf::Texture& AirPicture::GetPicture()
{
    return (_texture);
}
