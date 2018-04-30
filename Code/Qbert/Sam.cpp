#include "Sam.h"
#include "time.h"

Sam::Sam(float scale, __int16 screenWidth, float jumpCD )
	: Character(1, rand() % 2, scale, screenWidth, jumpCD)
{
	setTexture("./images/sam.png", 11, 16);
	setY(-14 * scale);

	if( getIndex( ) == 0 )
	{
		setTexRect( 5, 0 );
		setX( getX( ) - 16 * scale );
		setVX( 16 * scale / 30 );
		jumpState = 1;
	}
	else
	{
		setTexRect( 1, 0 );
		setX( getX( ) + 16 * scale );
		setVX( -16 * scale / 30 );
		jumpState = 2;
	}
	id = 7;
}


Sam::~Sam()
{ }


__int8 Sam::update(float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale);

	if (jumpTimer > jumpCDTime)
		Character::move(rand() % 2 + 1, scale );

	return retVal;
}


void Sam::moveAnimate(__int8 state)
{
	switch (state)
	{
	default:
	case 1: // Down Right Jump
		setTexRect(5, 0);
		break;
	case 2: // Down Left Jump
		setTexRect(1, 0);
		break;
	case 5: // Down Right Land
		setTexRect(4, 0);
		break;
	case 6: // Down Left Land
		setTexRect(0, 0);
		break;
	}
}
