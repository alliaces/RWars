#ifndef AIRTEXT_H_
#define AIRTEXT_H_

#include <SFML/Window.hpp>
#include "AirFont.h"
#include "AirWindow.h"
#include "IEntity.h"
#include "Vector2u.h"
#include "OnClickListener.h"

class AirText : public IEntity
{
public:
	AirText(AirFont *font, std::string text, Vector2u posText, sf::Color color, int sizeText);
	~AirText();
	sf::Sprite* GetSprite();
	sf::Font *getFont();
	void setFont(AirFont *font);
	sf::Text *GetText();
	std::string getTextString() const;
	void setTextString(const std::string &textString);
	const sf::Color &getColor() const;
	unsigned int getCharacterSize() const;
	void setCharacterSize(unsigned int size);
	void setColor(sf::Color color);
	Vector2u getPosition() const;
	void setPosition(const Vector2u &posText);
	void Update(AirWindow& win);
	void onClickHandler(OnClickListener* func);
private:
	sf::Text *text_;
	sf::Font *font_;
	OnClickListener *_onClick;
};

#endif
