/*
 * AirButton.h
 *
 *  Created on: 24 nov. 2015
 *      Author: lelong_t
 */

#ifndef SOURCES_AIRBUTTON_H_
#define SOURCES_AIRBUTTON_H_

#include <vector>
#include <SFML/Window.hpp>
#include "AirFont.h"
#include "AirPicture.h"
#include "IEntity.h"
#include "Vector2u.h"
#include "OnClickListener.h"

class AirButton : public IEntity
{
public:
	AirButton(AirPicture *res, AirPicture *clickRes, Vector2u posButton,
			Vector2u sizeButton, AirFont *font);
	~AirButton();
	void setText(std::string text, sf::Color color, int size);
	Vector2u getSpritePosition() const;
	void setSpritePosition(const sf::Vector2f &spritePos);
	sf::Sprite *GetSprite();
	sf::Text *GetText();
	const bool &getIsClick() const;
	void Update(AirWindow& win);
	void onClickHandler(OnClickListener *onclick);
	void setEnable(bool isEnable);
	bool getEnable() const;
private:
	sf::Sprite *sprite_;
	AirPicture *res_;
	AirPicture *clickres_;
	Vector2u sizeButton_;
	bool isClick_ = false;
	bool isEnable_;
	sf::Font *font_;
	sf::Text *text_;
	OnClickListener *_onClick;
};

#endif /* SOURCES_AIRBUTTON_H_ */
