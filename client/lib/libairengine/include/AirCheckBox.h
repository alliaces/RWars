#ifndef 	AIRCHECKBOX_H_
# define 	AIRCHECKBOX_H_

#include <vector>
#include <SFML/Window.hpp>
#include "AirFont.h"
#include "AirPicture.h"
#include "IEntity.h"
#include "Vector2u.h"
#include "OnClickListener.h"

class AirCheckBox : public IEntity
{
public:
	AirCheckBox(AirPicture *res, AirPicture *clickRes,
			Vector2u posCheckBox, Vector2u sizeCheckBox);
	~AirCheckBox();
	bool getIsChecked() const;
	void setIsChecked(bool isCheck);
	Vector2u getSpritePosition() const;
	void setSpritePosition(const sf::Vector2f &spritePos);
	sf::Sprite *GetSprite();
	sf::Text *GetText();
    void Update(AirWindow& win);
	void onClickHandler(OnClickListener *onclick);
private:
	bool isChecked_;
	AirPicture *res_;
	AirPicture *clickRes_;
	Vector2u sizeCheckBox_;
	sf::Sprite *sprite_;
	bool isClick_;
	OnClickListener *_onClick;
};

#endif
