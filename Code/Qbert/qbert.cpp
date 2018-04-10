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


void Qbert::move( __int8 direction, float scale, float fpsScale )
{
	Character::move( direction, scale, fpsScale );
	lastRow = getRow( );
	lastX = getX( );

	switch( direction )
	{
	case 3: // Up left
		targetX = getX( ) - 16 * scale;
	case 0: // Up right
		targetRow = getRow( ) - 1;
		break;
	case 1: // Down right
		targetX = getX( ) + 16 * scale;
	case 2: // Down left
		targetRow = getRow( ) + 1;
		break;
	default:
		break;
	}
}


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


__int16 Qbert::getTX( )
{
	return targetX;
}


__int8 Qbert::getTRow( )
{
	return targetRow;
}


__int16 Qbert::getLX( )
{
	return lastX;
}


__int8 Qbert::getLRow( )
{
	return lastRow;
}
