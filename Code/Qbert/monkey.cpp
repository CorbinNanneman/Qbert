#include "monkey.h"
#include "time.h"

Monkey::Monkey(float scale, __int16 screenWidth,
	float jumpCD) : Character(7, 7, scale, screenWidth, jumpCD)
{
	setTexture("./images/monkey.png", 16, 16);

	setX( getX( ) + 74 * scale );

	jumpState = 7;
	id = 2;
}


Monkey::~Monkey( )
{ }


__int8 Monkey::update(float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update( fpsScale, screenWidth, scale);

	if( jumpTimer > jumpCDTime )
		move( rand( ) % 2 + 5, scale, fpsScale );	

	return retVal;
}


void Monkey::moveAnimate(__int8 state)
{
	switch (state) 
	{
	case 5: //Jumping left
		setTexRect( 0, 0 );
		break;
	case 6: //Jumping right
		setTexRect( 4, 0 );
		break;
	case 9: //Resting left
		setTexRect( 1, 0 );
		break;
	case 10: //Resting right
		setTexRect( 5, 0 );
		break;
	default:
		break;
	}
}
