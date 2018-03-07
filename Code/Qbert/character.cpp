#include "character.h"

Character::Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth,
	float jumpCD ) 
	: GameObject( scale )
{
	row = startRow;
	index = startIndex;
	OOB = false;
	jumpCDTime = jumpCD;
	jumpTimer = 0;
	
	setX( 32 * scale * ( row * -.5 + index ) + screenWidth / 2 );
	setY( row * scale * 32 * .75 + 100 - 16 * scale );
	jumpDirection = 4;
}


Character::~Character() { }


__int8 Character::update( float fpsScale, __int16 screenWidth, float scale, __int16 frame )
{
	GameObject::update( );
	__int8 retVal = 0;
	jumpTimer += 1 / ( 60 / fpsScale );

	// Character is jumping
	if( jumpDirection < 4 )
	{
		// Character continues jumping
		if( jumpTimer < 0.5 || OOB )
		{
			setVY( getVY( ) + 9.8 * fpsScale * scale / ( 60 / fpsScale ) );

			if( OOB && isOffScreen( screenWidth, screenWidth, scale ) )
				retVal = 3;
			else
				retVal = 1;
			
			// Update collision coordinates
			switch( jumpDirection )
			{
			
			case 0: // Up right
				
				break;
			case 1: // Down right
				break;
			case 2: // Down left
				break;
			case 3: // Up left
				break;
			default:
				break;
			}
		}
		// Character completes jump
		else
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
				retVal = 2;
			}
		} // endif( jumpTimer > (fpsScale / 60) / 2 )
	} // endif( jumpDirection != 4 )

	/* retVal Glossary
	 0 - Default
	 1 - Character is jumping
	 2 - Character landed on cube
	 3 - Character fell off platform
	*/
	return retVal;
}


void Character::move( __int8 direction, float scale, float fpsScale )
{
	if( jumpTimer > jumpCDTime && !OOB )
	{
		moveAnimate( direction );
		switch( direction )
		{
		// Up right jump
		case 0:
			setVX( 16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -96 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Down Right jump
		case 1:
			setVX( 16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -48 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Down left jump
		case 2:
			setVX( -16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -48 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Up left jump
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


void Character::die( )
{
	getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
	row = -1;
	index = -1;
}


__int8 Character::getRow( )
{
	return row;
}


__int8 Character::getIndex( )
{
	return index;
}


__int8 Character::getDirection( )
{
	return jumpDirection;
}


bool Character::isOOB( )
{ 
	return OOB;
}


bool Character::isJumping( )
{
	return jumpDirection != 4;
}
