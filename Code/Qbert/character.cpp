#include "character.h"

#include <iostream>

Character::Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth ) : GameObject( scale )
{
	row = startRow;
	index = startIndex;
	
	setX( 32 * scale * ( row * -.5 + index ) + screenWidth / 2 );
	setY( row * scale * 32 * .75 + 100 - 16 * scale );
	setTexture( "./images/Qbert.png", 16, 16 );
}


Character::~Character() { }


void Character::update( int frame, __int8 fps, __int16 screenWidth, float scale )
{
	GameObject::update( );
	jumpTimer++;
	if( !isOOB && jumpTimer > fps / 2 )
	{
		setVX( 0 );
		setVY( 0 );
		setX( 32 * 2 * ( row * -.5 + index ) + screenWidth / 2 );
		setY( row * scale * 32 * .75 + 100 - 16 * scale );
	}
}


void Character::move( __int8 direction, float scale, __int8 fps )
{
	if( jumpTimer > fps && !isOOB )
	{
		switch( direction )
		{
		// Move up right
		case 0:
			row--;
			setVX( 16 * scale / (fps / 2) );
			setVY( -96 / 4 * scale / (fps / 2) );
			break;
		// Move down right
		case 1:
			row++;
			index++;
			setVX( 16 * scale / (fps / 2) );
			setVY( 96 / 4 * scale / (fps / 2) );
			break;
		// Move down left
		case 2:
			row++;
			setVX( -16 * scale / (fps / 2) );
			setVY( 96 / 4 * scale / (fps / 2) );
			break;
		// Move up left
		case 3:
			row--;
			index--;
			setVX( -16 * scale / (fps / 2) );
			setVY( -96 / 4 * scale / (fps / 2) );
			break;
		default:
			break;
		}

		// Check if the move is out of bounds
		if( row < 0 || row > 6 || index < 0 || index > row )
			isOOB = true;

		jumpTimer = 0;

		std::cout << "R: " << (int)row << " I: " << (int)index << '\n';
	}
}


void Character::checkOOB( )
{
	
}
