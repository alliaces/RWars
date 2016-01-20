#ifndef AIRFONT_H
#define AIRFONT_H

#include <SFML/Graphics.hpp>

class AirFont
{
    public:
        AirFont(const std::string& path);
        virtual ~AirFont();
        const sf::Font& GetFont();
    protected:
    private:
        sf::Font _font;
};

#endif // AIRFONT_H
