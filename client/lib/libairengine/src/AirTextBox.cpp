#include <iostream>
#include "AirTextBox.h"


AirTextBox::AirTextBox(AirPicture *res, Vector2u posTextBox, Vector2u sizeTextBox, AirFont *font)
{
	this->isClick_ = false;
	this->focus_ = false;
	this->font_ = (sf::Font*)&font->GetFont();
	this->res_ = res;
	this->sizeTextBox_.X = sizeTextBox.X;
	this->sizeTextBox_.Y = sizeTextBox.Y;
	this->text_ = new sf::Text();
	this->sprite_ = (new sf::Sprite(res->GetPicture()));
	this->sprite_->setScale(sf::Vector2f((float)(this->sizeTextBox_.X) / this->sprite_->getTexture()->getSize().x,
			(float)(this->sizeTextBox_.Y) / this->sprite_->getTexture()->getSize().y));
	this->sprite_->setPosition(sf::Vector2f(posTextBox.X, posTextBox.Y));
	this->_onClick = NULL;
	this->isPress = false;
}

AirTextBox::~AirTextBox()
{
}

void AirTextBox::onClickHandler(OnClickListener* func)
{
	this->_onClick = func;
}

/*
** getters / setters
*/
void AirTextBox::setText(std::string text, sf::Color color, int size)
{
	this->text_->setFont(*this->font_);
	this->text_->setString(text);
	this->text_->setCharacterSize((unsigned int) (size));
	this->text_->setPosition(sf::Vector2f(this->sprite_->getPosition().x + (this->sprite_->getGlobalBounds().width / 2) - (this->text_->getGlobalBounds().width / 2),
			this->sprite_->getPosition().y + (this->sprite_->getGlobalBounds().height / 2) - (this->text_->getGlobalBounds().height / 2 + 4)));
	this->text_->setColor(color);
}

Vector2u AirTextBox::getSpritePosition() const
{
	return (Vector2u(this->sprite_->getPosition().x, this->sprite_->getPosition().y));
}

void AirTextBox::setSpritePosition(const sf::Vector2f &spritePos)
{
	this->sprite_->setPosition(spritePos);
}

sf::Sprite *AirTextBox::GetSprite()
{
	return (this->sprite_);
}

std::string AirTextBox::getString()
{
	return (this->text_->getString());
}

sf::Text* AirTextBox::GetText()
{
	return (this->text_);
}

bool AirTextBox::getIsClick() const
{
	return (this->isClick_);
}

void AirTextBox::setIsClick(bool isClick)
{
	this->isClick_ = isClick;
}

/*
** Capture Text Enter
*/
void AirTextBox::OnTextEnter(std::string c)
{
  if (this->focus_ == true)
    {
      if (c == "\b")
	{
	  if (this->displayText_.size() > 0)
	    {
	      this->displayText_ = this->displayText_.erase(this->displayText_.size() - 1, 1);
	      this->text_->setString(this->displayText_);
	    }
	}
      else
	{
	  if (c[0] >= ' ' && this->text_->getGlobalBounds().width < this->sprite_->getGlobalBounds().width - this->text_->getCharacterSize() * 2)
	    {
	      this->displayText_ += c;
	      this->text_->setString(this->displayText_);
	    }
	}
      this->text_->setPosition(sf::Vector2f(this->sprite_->getPosition().x + (this->sprite_->getGlobalBounds().width / 2) - (this->text_->getGlobalBounds().width / 2),
					    this->sprite_->getPosition().y + (this->sprite_->getGlobalBounds().height / 2) - (this->text_->getGlobalBounds().height / 2 + 4)));
    }
}


/*
** Update Overload
*/

void AirTextBox::Update(AirWindow& win)
{
  pollText();
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      if (sf::Mouse::getPosition(win.GetWindows()).x >= this->sprite_->getPosition().x &&
	  sf::Mouse::getPosition(win.GetWindows()).x <= this->sprite_->getPosition().x + (this->sprite_->getTexture()->getSize().x * this->sprite_->getScale().x)
	  && sf::Mouse::getPosition(win.GetWindows()).y >= this->sprite_->getPosition().y &&
	  sf::Mouse::getPosition(win.GetWindows()).y <= this->sprite_->getPosition().y + (this->sprite_->getTexture()->getSize().y * this->sprite_->getScale().y))
	{
	  if (!this->isClick_)
	    this->focus_ = true;
	  this->isClick_ = true;
	}
      else
	{
	  this->focus_ = false;
	  this->isClick_ = false;
	}
    }
  else
    this->isClick_ = false;
}

void AirTextBox::pollText()
{
  for (int i = 0; i <= (int)sf::Keyboard::Key::Numpad9; ++i)
    {
	  if (i == sf::Keyboard::Key::LShift)
		  i++;
      if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
	{
	  if (!isPress)
	    {
		  std::string val = AirKeyboard::initMap(i);
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		val[0] -= 32;
	      OnTextEnter(val);
	    }
	  isPress = true;
	  return;
	}
    }
  isPress = false;
}
