#include "RedBall.h"
#include "time.h"

RedBall::RedBall( float scale, __int16 screenWidth, float jumpCD )
	: Character( 1, rand( ) % 2, scale, screenWidth, jumpCD )
{
	setTexture( "./images/RedBall.png", 15, 15 );
	setTexRect( 1, 0 );
	setY( -14 * scale );
	
	jumpState = 4;
	id = 4;
}


RedBall::~RedBall( )
{ }


__int8 RedBall::update( float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update( fpsScale, screenWidth, scale);

	if( jumpTimer > jumpCDTime )
		Character::move( rand() % 2 + 1, scale * fpsScale );

	return retVal;
}


void RedBall::moveAnimate( __int8 state )
{
	if( state < 5 )
		setTexRect( 1, 0 ); 
	else
		setTexRect( 0, 0);
}
