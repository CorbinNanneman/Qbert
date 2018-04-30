#include "MagicBall.h"
#include "time.h"

MagicBall::MagicBall(float scale, __int16 screenWidth, float jumpCD)
	: Character(1, rand() % 2, scale, screenWidth, jumpCD)
{
	setTexture("./images/magicBall.png", 10, 8);
	setTexRect(1, 0);
	
	setYOffset( 6 * scale );
	setY(-14 * scale);

	jumpState = 4;
	id = 5;
}


MagicBall::~MagicBall()
{ }


__int8 MagicBall::update(float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale);

	if (jumpTimer > jumpCDTime)
		Character::move(rand() % 2 + 1, scale );

	return retVal;
}


void MagicBall::moveAnimate(__int8 state)
{
	if (state < 5)
		setTexRect(1, 0);
	else
		setTexRect(0, 0);
}
