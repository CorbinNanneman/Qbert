#include "Slick.h"
#include "time.h"

Slick::Slick(float scale, __int16 screenWidth, float jumpCD)
	: Character(1, rand() % 2, scale, screenWidth, jumpCD)
{
	setTexture("./images/greenNerd.png", 14, 16);
	setTexRect(1, 0);
	// setX( 32 * scale * ( getRow( ) * -.5 + getIndex( ) ) + screenWidth / 2 );
	setY(-32 * scale);

	jumpState = 4;
	id = 6;
}


Slick::~Slick()
{}


__int8 Slick::update(float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale);

	if (jumpTimer > jumpCDTime)
		Character::move(rand() % 2 + 1, scale, fpsScale);

	return retVal;
}


void Slick::moveAnimate(__int8 state)
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
