#include "qbert.h"

Qbert::Qbert( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth )
	: Character( startRow, startIndex, scale, screenWidth, 0.5 )
{ 
	setTexture( "./images/Qbert.png", 16, 16 );
}

void Qbert::moveAnimate( __int8 state )
{
	switch( state )
	{
	default:
	case 0: // Up Right Jump
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	case 1: // Down Right Jump
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth * 5, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	case 2: // Down Left Jump
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth * 7, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	case 3: // Up Left Jump
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth * 3, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	case 4: // Up Right Land
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( 0, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	case 5: // Down Right Land
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth * 4, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	case 6: // Down Left Land
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth * 6, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	case 7: // Up Left Land
		getSprite( )->setTextureRect( sf::IntRect( sf::Vector2i( texWidth * 2, 0 ),
			sf::Vector2i( texWidth, texHeight ) ) );
		break;
	}
}


Qbert::~Qbert( )
{ }
