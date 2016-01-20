#ifndef AIRSPRITE_H
#define AIRSPRITE_H

#include "IEntity.h"
#include "AirPicture.h"
#include "Vector2u.h"

class AirSprite : public IEntity
{
    public:
        AirSprite(AirPicture* pict, const Vector2u& pos, const Vector2u& ssize);
        virtual ~AirSprite();
        sf::Sprite* GetSprite();
	sf::Text* GetText();
        void Update(AirWindow& win);
        Vector2u GetSize();
        void SetSize(const Vector2u& ssize);
        Vector2u GetPos();
        void SetPos(const Vector2u& ssize);
        void SetPicture(AirPicture* pict);
    protected:
    private:
    AirPicture* pict_;
    sf::Sprite _sprite;
    Vector2u size_;
};

#endif // AIRSPRITE_H
