/*
 * AirButton.cpp
 *
 *  Created on: 24 nov. 2015
 *      Author: lelong_t
 */

#include "AirButton.h"

AirButton::AirButton(AirPicture *res, AirPicture *clickRes, Vector2u posButton,
		Vector2u sizeButton, AirFont *font)
{
	this->isEnable_ = true;
	this->font_ = (sf::Font*)&font->GetFont();
	this->res_ = res;
	this->clickres_ = clickRes;
	this->sizeButton_.X = sizeButton.X;
	this->sizeButton_.Y = sizeButton.Y;
	this->text_ = new sf::Text();
	this->sprite_ = (new sf::Sprite(res->GetPicture()));
	this->sprite_->setScale(sf::Vector2f((float)(this->sizeButton_.X) / this->sprite_->getTexture()->getSize().x,
			(float)(this->sizeButton_.Y) / this->sprite_->getTexture()->getSize().y));
	this->sprite_->setPosition(sf::Vector2f(posButton.X, posButton.Y));
	this->_onClick = NULL;
}

AirButton::~AirButton()
{
}

void AirButton::onClickHandler(OnClickListener* func)
{
	this->_onClick = func;
}

/*
** getters / setters
*/

void AirButton::setEnable(bool isEnable)
{
	this->isEnable_ = isEnable;
}

bool AirButton::getEnable() const
{
	return (this->isEnable_);
}

void AirButton::setText(std::string text, sf::Color color, int size)
{
	this->text_->setFont(*this->font_);
	this->text_->setString(text);
	this->text_->setCharacterSize((unsigned int) (size));
	this->text_->setPosition(sf::Vector2f(this->sprite_->getPosition().x + (this->sprite_->getGlobalBounds().width / 2) - (this->text_->getGlobalBounds().width / 2),
			this->sprite_->getPosition().y + (this->sprite_->getGlobalBounds().height / 2) - (this->text_->getGlobalBounds().height / 2 + 4)));
	this->text_->setColor(color);
}

Vector2u AirButton::getSpritePosition() const
{
	return (Vector2u(this->sprite_->getPosition().x, this->sprite_->getPosition().y));
}

void AirButton::setSpritePosition(const sf::Vector2f &spritePos)
{
	this->sprite_->setPosition(spritePos);
}

sf::Sprite *AirButton::GetSprite()
{
	return (this->sprite_);
}

sf::Text *AirButton::GetText()
{
	return (this->text_);
}

const bool &AirButton::getIsClick() const
{
	return (this->isClick_);
}

/*
** Update Overload
*/

void AirButton::Update(AirWindow& win)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
        if (sf::Mouse::getPosition(win.GetWindows()).x >= this->sprite_->getPosition().x &&
        		sf::Mouse::getPosition(win.GetWindows()).x <= this->sprite_->getPosition().x + (this->sprite_->getTexture()->getSize().x * this->sprite_->getScale().x)
            && sf::Mouse::getPosition(win.GetWindows()).y >= this->sprite_->getPosition().y &&
			sf::Mouse::getPosition(win.GetWindows()).y <= this->sprite_->getPosition().y + (this->sprite_->getTexture()->getSize().y * this->sprite_->getScale().y))
        {
        	this->isClick_ = true;
        	this->sprite_->setTexture(clickres_->GetPicture());
        	this->sprite_->setScale(sf::Vector2f((float)(this->sizeButton_.X) / this->sprite_->getTexture()->getSize().x,
        			(float)(this->sizeButton_.Y) / this->sprite_->getTexture()->getSize().y));
        }
        else
        {
            this->sprite_->setTexture(res_->GetPicture());
            this->sprite_->setScale(sf::Vector2f((float)(this->sizeButton_.X) / this->sprite_->getTexture()->getSize().x,
            		(float)(this->sizeButton_.Y) / this->sprite_->getTexture()->getSize().y));
        }
	}
	else
	{
		if (this->isClick_)
		{
			if (this->_onClick != NULL && this->isEnable_)
				_onClick->OnClick((void*) this);
		}
		this->isClick_ = false;
		this->sprite_->setTexture(res_->GetPicture());
		this->sprite_->setScale(sf::Vector2f((float)(this->sizeButton_.X) / this->sprite_->getTexture()->getSize().x,
				(float)(this->sizeButton_.Y) / this->sprite_->getTexture()->getSize().y));
	}
}
