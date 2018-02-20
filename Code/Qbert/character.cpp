#include "character.h"

Character::Character( __int8 startRow, __int8 startIndex, __int8 scale, float screenWidth )
{
	row = startRow;
	index = startIndex;
	
	setX( 32 * scale * ( row * -.5 + index ) + screenWidth / 2 );
	setY( row * scale * 32 * .75 + 100 - 16 * scale );
	setTexture( "./images/Qbert.png", 16, 16 );
}


Character::~Character() { }


void Character::update( int frame )
{
	GameObject::update( );
	jumpTimer++;
	if( !isOOB && jumpTimer > 60 )
	{
		setVX( 0 );
		setVY( 0 );
	}
}


void Character::move( __int8 direction, __int8 scale )
{
	if( jumpTimer > 60 )
	{
		switch( direction )
		{
		// Move up right
		case 0:
			row--;
			setVX( 32 * scale / 60 );
			break;
		// Move down right
		case 1:
			row++;
			index++;
			break;
		// Move down left
		case 2:
			row++;
			break;
		// Move up left
		case 3:
			row--;
			index--;
			break;
		default:
			break;
		}

		// Check if the move is out of bounds
		if( row < 0 || row > 6 || index < 0 || index > row + 1 )
			isOOB = true;

		jumpTimer = 0;
		
		setX( 32 * 1 * ( row * -.5 + index ) + 800 / 2 );
		setY( row * 1 * 32 * .75 + 100 - 16 * 1 );
	}
}


void Character::checkOOB( )
{
	
}
