#include "redball.h"
#include "time.h"

RedBall::RedBall( float scale, __int16 screenWidth, float jumpCD )
	: Character( 1, rand( ) % 2, scale, screenWidth, jumpCD )
{
	setTexture( "./images/RedBall.png", 15, 15 );
}

__int8 RedBall::update( float fpsScale, __int16 screenWidth, float scale, __int16 frame )
{
	__int8 retVal = Character::update( fpsScale, screenWidth, scale, frame );

	if( jumpTimer > jumpCDTime )
		Character::move( rand() % 2 + 1, scale, fpsScale );

	return retVal;
}

void RedBall::moveAnimate( __int8 state )
{
	if( state < 4 )
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
	else
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( 0, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
}


RedBall::~RedBall( )
{ }
