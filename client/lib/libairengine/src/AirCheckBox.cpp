#include "AirCheckBox.h"

AirCheckBox::AirCheckBox(AirPicture *res, AirPicture *clickRes,
		Vector2u posCheckBox, Vector2u sizeCheckBox)
{
	this->isChecked_ = false;
	this->isClick_ = false;
	this->res_ = res;
	this->clickRes_ = clickRes;
	this->sizeCheckBox_.X = sizeCheckBox.X;
	this->sizeCheckBox_.Y = sizeCheckBox.Y;
	this->sprite_ = (new sf::Sprite(res->GetPicture()));
	this->sprite_->setScale(sf::Vector2f((float)(this->sizeCheckBox_.X) / this->sprite_->getTexture()->getSize().x,
			(float)(this->sizeCheckBox_.Y) / this->sprite_->getTexture()->getSize().y));
	this->sprite_->setPosition(sf::Vector2f(posCheckBox.X, posCheckBox.Y));
	this->_onClick = NULL;
}

AirCheckBox::~AirCheckBox()
{
}

void AirCheckBox::onClickHandler(OnClickListener* func)
{
	this->_onClick = func;
}

/*
** getters / setters
*/

bool AirCheckBox::getIsChecked() const
{
	return (this->isChecked_);
}

void AirCheckBox::setIsChecked(bool isCheck)
{
	this->isChecked_ = isCheck;
}

Vector2u AirCheckBox::getSpritePosition() const
{
	return (Vector2u(this->sprite_->getPosition().x, this->sprite_->getPosition().y));
}

void AirCheckBox::setSpritePosition(const sf::Vector2f &spritePos)
{
	this->sprite_->setPosition(spritePos);
}

sf::Sprite *AirCheckBox::GetSprite()
{
	return (this->sprite_);
}

sf::Text *AirCheckBox::GetText()
{
	return (NULL);
}

/*
** Update Overload
*/

void AirCheckBox::Update(AirWindow& win)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
        if (sf::Mouse::getPosition(win.GetWindows()).x >= this->sprite_->getPosition().x &&
        		sf::Mouse::getPosition(win.GetWindows()).x <= this->sprite_->getPosition().x + (this->sprite_->getTexture()->getSize().x * this->sprite_->getScale().x)
            && sf::Mouse::getPosition(win.GetWindows()).y >= this->sprite_->getPosition().y &&
			sf::Mouse::getPosition(win.GetWindows()).y <= this->sprite_->getPosition().y + (this->sprite_->getTexture()->getSize().y * this->sprite_->getScale().y))
        {
            if (!this->isClick_)
            {
                this->isChecked_ = !this->isChecked_;
                if (this->isChecked_)
                    this->sprite_->setTexture(this->clickRes_->GetPicture());
                else
                    this->sprite_->setTexture(this->res_->GetPicture());
                this->sprite_->setScale(sf::Vector2f((float)(this->sizeCheckBox_.X) / this->sprite_->getTexture()->getSize().x,
                		(float)(this->sizeCheckBox_.Y) / this->sprite_->getTexture()->getSize().y));
            }
            this->isClick_ = true;
        }
        else
    	    this->isClick_ = false;
	}
	else
	    this->isClick_ = false;
}
