#ifndef IENTITY_H
#define IENTITY_H

#include <SFML/Graphics.hpp>
#include "AirWindow.h"

class IEntity
{
    public:
        virtual ~IEntity() {}
        virtual sf::Sprite* GetSprite() = 0;
        virtual sf::Text* GetText() = 0;
	virtual void Update(AirWindow& win) = 0;
    protected:
    private:
};

#endif // IENTITY_H
