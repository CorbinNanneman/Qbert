#include "lankyDude.h"



LankyDude::LankyDude(float scale, __int16 screenWidth,
	float jumpCD) : Character(7, 0, scale, screenWidth, jumpCD)
{
	setTexture("./images/lankyDude.png", 16, 16);

	setX(getX() - 74 * scale);

	jumpState = 10;
}

__int8 LankyDude::update(float fpsScale, __int16 screenWidth, float scale, __int16 frame)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale, frame);

	if (jumpTimer > jumpCDTime)
		move(rand() % 2 + 8, scale, fpsScale);

	return retVal;
}


void LankyDude::moveAnimate(__int8 state)
{
	switch (state)
	{
	case 8: //Jumping left
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth * 4, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 9: //Jumping right
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 12: //Resting left
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth* 5, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 13: //Resting right
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	default:
		break;
	}
}

LankyDude::~LankyDude()
{
}
