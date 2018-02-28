#include "redball.h"
#include "time.h"

RedBall::RedBall( float scale, __int16 screenWidth )
	: Character( 1, rand( ) % 2, scale, screenWidth )
{
	setTexture( "./images/RedBall.png", 15, 15 );
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
