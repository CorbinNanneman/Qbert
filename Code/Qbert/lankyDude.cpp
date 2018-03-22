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
		updateTexRect( 4, 0 );
		break;
	case 9: //Jumping right
		updateTexRect( 0, 0 );
		break;
	case 12: //Resting left
		updateTexRect( 5, 0 );
		break;
	case 13: //Resting right
		updateTexRect( 1, 0 );
		break;
	default:
		break;
	}
}

LankyDude::~LankyDude()
{
}
