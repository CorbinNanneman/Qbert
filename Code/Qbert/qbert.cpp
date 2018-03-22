#include "qbert.h"

Qbert::Qbert( float scale = 0, __int16 screenWidth = 0 )
	: Character( 0, 0, scale, screenWidth, 0.5 )
{ 
	setTexture( "./images/Qbert.png", 16, 16 );
	updateTexRect( 4, 0 );
	jumpState = 11;
}


void Qbert::moveAnimate( __int8 state )
{
	switch( state )
	{
	default:
	case 0: // Up Right Jump
		updateTexRect( 1, 0 );
		break;
	case 1: // Down Right Jump
		updateTexRect( 5, 0 );
		break;
	case 2: // Down Left Jump
		updateTexRect( 7, 0 );
		break;
	case 3: // Up Left Jump
		updateTexRect( 3, 0 );
		break;
	case 4: // Up Right Land
		updateTexRect( 0, 0 );
		break;
	case 5: // Down Right Land
		updateTexRect( 4, 0 );
		break;
	case 6: // Down Left Land
		updateTexRect( 6, 0 );
		break;
	case 7: // Up Left Land
		updateTexRect( 2, 0 );
		break;
	}
}


Qbert::~Qbert( )
{ }
