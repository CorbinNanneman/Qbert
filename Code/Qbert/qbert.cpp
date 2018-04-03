#include "qbert.h"

Qbert::Qbert( float scale = 0, __int16 screenWidth = 0 )
	: Character( 0, 0, scale, screenWidth, 0.5 )
{ 
	setTexture( "./images/Qbert.png", 16, 16 );
	setTexRect( 4, 0 );

	jumpState = 11;
	id = 0;
}


Qbert::~Qbert( )
{ }


void Qbert::moveAnimate( __int8 state )
{
	switch( state )
	{
	default:
	case 0: // Up Right Jump
		setTexRect( 1, 0 );
		break;
	case 1: // Down Right Jump
		setTexRect( 5, 0 );
		break;
	case 2: // Down Left Jump
		setTexRect( 7, 0 );
		break;
	case 3: // Up Left Jump
		setTexRect( 3, 0 );
		break;
	case 4: // Up Right Land
		setTexRect( 0, 0 );
		break;
	case 5: // Down Right Land
		setTexRect( 4, 0 );
		break;
	case 6: // Down Left Land
		setTexRect( 6, 0 );
		break;
	case 7: // Up Left Land
		setTexRect( 2, 0 );
		break;
	}
}
