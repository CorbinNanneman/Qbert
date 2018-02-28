#include "character.h"

Character::Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth,
	float jumpCD ) 
	: GameObject( scale )
{
	row = startRow;
	index = startIndex;
	jumpCDTime = jumpCD;
	jumpDirection = 4;
	jumpTimer = 0;
	
	setX( 32 * scale * ( row * -.5 + index ) + screenWidth / 2 );
	setY( row * scale * 32 * .75 + 100 - 16 * scale );
	setTexture( "./images/Qbert.png", 16, 16 );
}


Character::~Character() { }


void Character::update( float fpsScale, __int16 screenWidth, float scale, __int16 frame )
{
	GameObject::update( );
	jumpTimer += 1 / ( 60 / fpsScale );

	// Jump calculations, when character is jumping
	if( jumpDirection != 4 )
	{
		// Character continues jumping
		setVY( getVY( ) + 9.8 * fpsScale * scale / ( 60 / fpsScale ) );

		// Character completes jump
		if( jumpTimer > 0.5 )
		{
			// Adjust character position
			switch( jumpDirection )
			{
			case 0: // Up right
				row--;
				break;
			case 1: // Down right
				row++;
				index++;
				break;
			case 2: // Down left
				row++;
				break;
			case 3: // Up left
				row--;
				index--;
				break;
			default:
				break;
			}

			// OOB Check
			if( row < 0 || row > 6 || index < 0 || index > row )
				OOB = true;
			else
			{
				moveAnimate( jumpDirection + 4 );
				// Ensure Exact Position
				setVX( 0 );
				setVY( 0 );
				setX( 32 * scale * ( row * -.5 + index ) + screenWidth / 2 );
				setY( scale * ( row * 24 - 16 ) + 100 );
				jumpDirection = 4; // Stopped moving
			}
		} // endif( jumpTimer > (fpsScale / 60) / 2 )
	} // endif( jumpDirection != 4 )
}


void Character::move( __int8 direction, float scale, float fpsScale )
{
	if( jumpTimer > jumpCDTime && !OOB )
	{
		moveAnimate( direction );
		switch( direction )
		{
		// Move up right
		case 0:
			setVX( 16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -96 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Move down right
		case 1:
			setVX( 16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -48 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Move down left
		case 2:
			setVX( -16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -48 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Move up left
		case 3:
			setVX( -16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -96 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		default:
			break;
		}

		jumpTimer = 0;
		jumpDirection = direction;
	}
}


bool Character::isOOB( )
{ 
	return OOB;
}
