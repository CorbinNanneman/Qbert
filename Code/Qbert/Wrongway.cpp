#include "Wrongway.h"

Wrongway::Wrongway(float scale, __int16 screenWidth,
	float jumpCD) : Character(7, 0, scale, screenWidth, jumpCD)
{
	setTexture("./images/wrongway.png", 16, 16);
	setX(getX() - 74 * scale);

	jumpState = 10;
	id = 3;
}


Wrongway::~Wrongway( )
{ }


__int8 Wrongway::update(float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale);

	if (jumpTimer > jumpCDTime)
		move(rand() % 2 + 8, scale );

	return retVal;
}


void Wrongway::moveAnimate(__int8 state)
{
	switch (state)
	{
	case 8: //Jumping left
		setTexRect( 4, 0 );
		break;
	case 9: //Jumping right
		setTexRect( 0, 0 );
		break;
	case 12: //Resting left
		setTexRect( 5, 0 );
		break;
	case 13: //Resting right
		setTexRect( 1, 0 );
		break;
	default:
		break;
	}
}
