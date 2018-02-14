#include "character.h"

Character::Character( uint8_t startRow, uint8_t startIndex, int scale, double screenWidth )
{
	row = startRow;
	index = startIndex;

	setX( 32 * scale * ( row * -.5 + index ) + screenWidth / 2 );
	setY( row * scale * 32 * .75 + 100 - 16 * scale );
	setTexture( "./images/Qbert.png", 16, 16 );
}


Character::~Character()
{
}


void Character::update( int frame )
{
	if( !isOOB )
		jumpTimer++;
}


void Character::moveUR( )
{
	if ( jumpTimer > 60 )
	{
		row--;
		setX( 32 * 1 * ( row * -.5 + index ) + 800 / 2 );
		setY( row * 1 * 32 * .75 + 100 - 16 * 1 );
		jumpTimer = 0;
	}
}


void Character::moveDR( )
{

}


void Character::moveDL( )
{

}


void Character::moveUL( )
{

}


bool Character::moveOOB( uint8_t row, uint8_t index )
{
	return row < 0 || row > 6 || index < 0 || index > row;
}
