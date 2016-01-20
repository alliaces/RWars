#include "AirSprite.h"

AirSprite::~AirSprite()
{
    //dtor
}

AirSprite::AirSprite(AirPicture* pict, const Vector2u& pos, const Vector2u& ssize) : _sprite(pict->GetPicture())
{
    pict_ = pict;
    size_.X = ssize.X;
    size_.Y = ssize.Y;
    _sprite.setPosition(sf::Vector2f(pos.X, pos.Y));
    _sprite.setScale(sf::Vector2f(float(ssize.X)/_sprite.getTexture()->getSize().x, float(ssize.Y)/_sprite.getTexture()->getSize().y));
}

sf::Sprite* AirSprite::GetSprite()
{
    return (&_sprite);
}

sf::Text* AirSprite::GetText()
{
  return (NULL);
}

void AirSprite::Update(AirWindow& win)
{
  (void)win;
}

Vector2u AirSprite::GetSize()
{
    return (Vector2u(_sprite.getTexture()->getSize().x * _sprite.getScale().x, _sprite.getTexture()->getSize().y * _sprite.getScale().y));
}

void AirSprite::SetPicture(AirPicture* pict)
{
    if (pict != pict_)
    {
        pict_ = pict;
        _sprite.setTexture(pict->GetPicture());
        this->SetSize(size_);
    }
}

void AirSprite::SetSize(const Vector2u& ssize)
{
    size_.X = ssize.X;
    size_.Y = ssize.Y;
    _sprite.setScale(sf::Vector2f(float(ssize.X)/_sprite.getTexture()->getSize().x, float(ssize.Y)/_sprite.getTexture()->getSize().y));
}

Vector2u AirSprite::GetPos()
{
    return (Vector2u(_sprite.getPosition().x, _sprite.getPosition().y));
}

void AirSprite::SetPos(const Vector2u& ssize)
{
    _sprite.setPosition(ssize.X, ssize.Y);
}
