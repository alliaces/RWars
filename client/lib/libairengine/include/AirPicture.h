#ifndef AIRPICTURE_H
#define AIRPICTURE_H

#include <SFML/Graphics.hpp>

class AirPicture
{
    public:
        AirPicture(const std::string &);
        virtual ~AirPicture();
        sf::Texture& GetPicture();
    protected:
    private:
        sf::Texture _texture;
};

#endif // AIRPICTURE_H
