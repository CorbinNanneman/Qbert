#include "redball.h"
#include "time.h"

RedBall::RedBall( float scale, __int16 screenWidth, float jumpCD )
	: Character( 1, rand( ) % 2, scale, screenWidth, jumpCD )
{
	setTexture( "./images/RedBall.png", 15, 15 );
	updateTexRect( 1, 0 );
	// setX( 32 * scale * ( getRow( ) * -.5 + getIndex( ) ) + screenWidth / 2 );
	setY( -32 * scale );
	
	jumpState = 4;
}


RedBall::~RedBall( )
{ }


__int8 RedBall::update( float fpsScale, __int16 screenWidth, float scale, __int16 frame )
{
	__int8 retVal = Character::update( fpsScale, screenWidth, scale, frame );

	if( jumpTimer > jumpCDTime )
		Character::move( rand() % 2 + 1, scale, fpsScale );

	return retVal;
}


void RedBall::moveAnimate( __int8 state )
{
	if( state < 5 )
		updateTexRect( 1, 0 ); 
	else
		updateTexRect( 0, 0);
}
