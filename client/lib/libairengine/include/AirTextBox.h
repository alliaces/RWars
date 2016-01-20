#ifndef		AIRTEXTBOX_H_
# define	AIRTEXTBOX_H_

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <map>
#include "AirFont.h"
#include "AirPicture.h"
#include "IEntity.h"
#include "Vector2u.h"
#include "OnClickListener.h"
#include "AirKeyboard.h"

class AirTextBox : public IEntity
{
public:
	AirTextBox(AirPicture *res, Vector2u posTextBox, Vector2u sizeTextBox, AirFont *font);
	~AirTextBox();
	void setText(std::string, sf::Color color, int size);
	Vector2u getSpritePosition() const;
	void setSpritePosition(const sf::Vector2f &spritePos);
	sf::Sprite *GetSprite();
	sf::Text* GetText();
	std::string getString();
	bool getIsClick() const;
	void setIsClick(bool isClick);
	void OnTextEnter(std::string c);
	void Update(AirWindow& win);
	void onClickHandler(OnClickListener *onclick);
private:
	void pollText();
	sf::Sprite *sprite_;
	AirPicture *res_;
	Vector2u sizeTextBox_;
	bool isClick_;
	bool focus_;
	sf::Font *font_;
	sf::Text *text_;
	std::string displayText_;
	OnClickListener *_onClick;
//	std::map<int, std::string> _keys;
	bool isPress;
};

#endif
