#include "AirText.h"

AirText::AirText(AirFont *font, std::string text, Vector2u posText, sf::Color color, int sizeText)
{
	this->font_ = (sf::Font*)&font->GetFont();
	this->text_ = new sf::Text();
	this->text_->setFont(*this->font_);
	this->text_->setString(text);
	this->text_->setCharacterSize((unsigned int) (sizeText));
	this->text_->setPosition(sf::Vector2f(posText.X, posText.Y));
	this->text_->setColor(color);
	this->_onClick = NULL;
}

AirText::~AirText()
{
}

void AirText::onClickHandler(OnClickListener* func)
{
	this->_onClick = func;
}

/*
** getters / setters
*/
sf::Sprite* AirText::GetSprite()
{
	return (NULL);
}

sf::Font *AirText::getFont()
{
	return (this->font_);
}

void AirText::setFont(AirFont *font)
{
	this->font_ = (sf::Font*)&font->GetFont();
}

sf::Text *AirText::GetText()
{
	return (this->text_);
}

std::string AirText::getTextString() const
{
	return (this->text_->getString());
}

void AirText::setTextString(const std::string &textString)
{
	this->text_->setString(textString);
}

const sf::Color &AirText::getColor() const
{
	return (this->text_->getColor());
}

void AirText::setColor(sf::Color color)
{
	this->text_->setColor(color);
}

unsigned int AirText::getCharacterSize() const
{
	return (this->text_->getCharacterSize());
}

void AirText::setCharacterSize(unsigned int size)
{
	this->text_->setCharacterSize(size);
}

Vector2u AirText::getPosition() const
{
	return (Vector2u(this->text_->getPosition().x, this->text_->getPosition().y));
}

void AirText::setPosition(const Vector2u &posText)
{
  this->text_->setPosition(sf::Vector2f(posText.X, posText.Y));
}

/*
** Update Overload
*/
void AirText::Update(AirWindow& win)
{
	(void) win;
}
