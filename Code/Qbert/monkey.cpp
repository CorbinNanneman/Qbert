#include "monkey.h"
#include "time.h"

Monkey::Monkey(float scale, __int16 screenWidth,
	float jumpCD) : Character(7, 7, scale, screenWidth, jumpCD)
{
	setTexture("./images/monkey.png", 16, 16);
	jumpDirection = 9;
}


Monkey::~Monkey( )
{ }


__int8 Monkey::update(float fpsScale, __int16 screenWidth, float scale, __int16 frame)
{
	__int8 retVal = Character::update( fpsScale, screenWidth, scale, frame );

	if( jumpTimer > jumpCDTime )
		move( rand( ) % 2 + 5, scale, fpsScale );	

	return retVal;
}


void Monkey::moveAnimate(__int8 state)
{
	switch (state) 
	{
	case 9: //Resting left
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 10: //Resting right
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth *5, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 5: //Jumping left
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 6: //Jumping right
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth*4, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	}
}
