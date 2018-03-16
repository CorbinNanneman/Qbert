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
	
	setX( 32 * scale * ( row * -.5f + index ) + screenWidth / 2 );
	setY( scale * ( row * 24 - 16 ) + 100 );
	jumpDirection = 4;
}


Character::~Character() { }


__int8 Character::update( float fpsScale, __int16 screenWidth, float scale, __int16 frame )
{
	GameObject::update( );
	__int8 retVal = 0;
	jumpTimer += 1 / ( 60 / fpsScale );

	// Character is jumping
	if( jumpDirection < 9 )
	{
		// Character continues jumping
		if( jumpTimer < 0.5 || OOB )
		{
			// Apply gravity
			if( jumpDirection < 5 ) // Normal characters
				setVY( getVY( ) + 9.8f * fpsScale * scale / ( 60 / fpsScale ) );
			else if( jumpDirection < 7 ) // RtL Monkey
				setVX( getVX( ) - 9.8 * fpsScale * scale / ( 60 / fpsScale ) );
			else if( jumpDirection < 9 ) // LtR Monkey
				;

			if( OOB && isOffScreen( screenWidth, screenWidth, scale ) )
				retVal = 3;
			else
				retVal = 1;
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
			case 5: // Monkey up left
				row--;
				index--;
				break;
			case 6: // Left
				index--;
			default:
				break;
			}

			// OOB Checking
			switch( jumpDirection )
			{
			case 0: // Up right
				if( index > row )
					OOB = true;
				break;
			case 1: // Down right
			case 2: // Down left
				if( row > 6 )
					OOB = true;
				break;
			case 3: // Up left
				if( index < 0 )
					OOB = true;
				break;
			case 5: // Monkey up left
			case 6: // Monkey left
				if( index < 1 )
					OOB = true;
				break;
			case 7: // Monkey up right
			case 8: // Monkey right
				if( index > row - 1 )
					OOB = true;
				break;
			default:
				break;
			}

			// Charcater succesfully lands on block
			if( !OOB )
			{
				moveAnimate( jumpDirection + 4 );
				// Ensure Exact Position
				setVX( 0 );
				setVY( 0 );
				setX( 32 * scale * ( row * -.5 + index ) + screenWidth / 2 );
				setY( scale * ( row * 24 - 16 ) + 100 );
				jumpDirection = 9; // Stopped moving
				retVal = 2;
			}
		} // endif( jumpTimer > 0.5 )
	} // endif( jumpDirection != 5 )

	/* retVal Glossary
	 0 - Default
	 1 - Character is jumping
	 2 - Character landed on cube
	 3 - Character fell off screen
	*/
	return retVal;
}


void Character::move( __int8 direction, float scale, float fpsScale )
{
	if( jumpTimer > jumpCDTime && !OOB )
	{
		moveAnimate( direction );
		switch( direction ) // Set jump velocities
		{
		// Up Right
		case 0:
			setVX( 16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -96 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Down Right
		case 1:
			setVX( 16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -48 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Down Left
		case 2:
			setVX( -16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -48 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Up Left
		case 3:
			setVX( -16 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -96 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Monkey Up Left
		case 5:
			setVX( 56 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( -22 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		// Left
		case 6:
			setVX( 40 * scale / ( ( 60 / fpsScale ) / 2 ) );
			setVY( 2 * scale / ( ( 60 / fpsScale ) / 2 ) );
			break;
		default:
			break;
		}

		jumpTimer = 0;
		jumpDirection = direction;
	}
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
