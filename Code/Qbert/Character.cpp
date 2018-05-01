#include "Character.h"

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
	setY( scale * ( row * 24 + 34 ) );
	jumpState = 4;
}


Character::~Character() 
{ }


/** Jump State Glossary
0 - Normal Up Right
1 - Normal Down Right
2 - Normal Down Left
3 - Normal Up Left
4 - Normal Spawn In*

5 - RtL Monkey Up Left
6 - RtL Monkey Left
7 - RtL Monkey Spawn In*

8 - LtR Up Right
9 - LtR Right
10 - LtR Spawn In*

11 - Character Not Moving

*Spawn In exists to allow an animation when a character is spawned
*/
void Character::move( __int8 direction, float scale )
{
	// Movement scale is precomputed value of scale * fpsScale
	if( jumpTimer > jumpCDTime && !OOB )
	{
		moveAnimate( direction );
		switch( direction ) // Set jump velocities
		{
			//scale * fpsscale
		// Up Right
		case 0:
			setVX( 16 * scale / 30 );
			setVY( -96 * scale / 30 );
			break;
		// Down Right
		case 1:
			setVX( 16 * scale / 30 );
			setVY( -46 * scale / 30 );
			break;
		// Down Left
		case 2:
			setVX( -16 * scale / 30 );
			setVY( -46 * scale / 30 );
			break;
		// Up Left
		case 3:
			setVX( -16 * scale / 30 );
			setVY( -96 * scale / 30 );
			break;
		// RtL Up Left
		case 5:
			setVX( 56 * scale / 30 );
			setVY( -24 * scale / 30 );
			break;
		// RtL Left
		case 6:
			setVX( 40 * scale / 30 );
			break;
		// LtR Up Right
		case 8: 
			setVX(-56 * scale / 30 );
			setVY(-24 * scale / 30 );
			break;
		// LtR Right
		case 9:
			setVX(-40 * scale / 30 );
			break;
		default:
			break;
		}

		// Adjust character position
		switch( direction )
		{
		case 3: // Up left
		case 5: // RtL up left
			index--;
		case 0: // Up right
		case 8: // LtR Up Right
			row--;
			break;
		case 1: // Down right
			index++;
		case 2: // Down left
			row++;
			break;
		case 6: // RtL left
			index--;
			break;
		case 9: // LtR Right
			index++;
			break;
		default:
			break;
		}

		// OOB Checking
		switch( direction )
		{
			// Normal characters
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
			// RtL Monkey
		case 5: // Up left
		case 6: // Left
			if( index < 1 )
				OOB = true;
			break;
			// LtR Monkey
		case 8: // Monkey up right
		case 9: // Monkey right
			if( index > row - 1 )
				OOB = true;
			break;
		default:
			break;
		}

		jumpTimer = 0;
		jumpState = direction;
	}
}


__int8 Character::update( float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = 0; // See Glossary at end of function.
	jumpTimer += fpsScale / 60;

	// Character is jumping
	if( jumpState < 11 )
	{
		// Character continues jumping
		if( jumpTimer < 0.5f || OOB )
		{
			// Apply gravity
			if( jumpState < 5 ) // Normal characters
				setVY( getVY( ) + 9.8f * scale * fpsScale / 60 );
			else if( jumpState < 8 ) // RtL Monkey
				setVX( getVX( ) - 9.8f * scale * fpsScale / 60 );
			else if( jumpState < 11 ) // LtR Monkey
				setVX( getVX( ) + 9.8f * scale * fpsScale / 60 );

			if( OOB && isOffScreen( screenWidth, screenWidth, scale ) )
				retVal = 3;
			else
				retVal = 1;
		}
		// Character completes jump
		if( jumpTimer > 0.5f && jumpTimer < 0.6f )
		{
			// Character succesfully lands on block
			if( !OOB )
			{
				moveAnimate( jumpState + 4 );
				// Ensure Exact Position
				setVX( 0 );
				setVY( 0 );
				setX( 32 * scale * ( row * -.5f + index ) + screenWidth / 2 );
				setY( scale * ( row * 24 + 34 ) );
				setZ( getRow( ) + 1 );
				// Stop Moving
				jumpState = 11;
				retVal = 2;
			}
			// Character falls OOB 
			else if( getRow( ) < 6 )
				setZ( -1 );
		} // endif( jumpTimer > 0.5 )
	} // endif( jumpState != 5 )

	GameObject::update( fpsScale );

	/** RetVal Glossary
	 0 - Default
	 1 - Character is jumping
	 2 - Character landed on cube
	 3 - Character fell off screen
	*/
	return retVal;
}


void Character::setRow( __int8 newRow, float scale, __int16 screenWidth )
{
	row = newRow;
	setX( 32 * scale * ( row * -.5f + index ) + screenWidth / 2 );
	setY( scale * ( row * 24 + 34 ) );
	setZ( getRow( ) + 1 );
	jumpState = 11;
	OOB = false;
}


void Character::setIndex( __int8 newIndex, float scale, __int16 screenWidth )
{
	index = newIndex;
	setX( 32 * scale * ( row * -.5f + index ) + screenWidth / 2 );
	setY( scale * ( row * 24 + 34 ) );
	setZ( getRow( ) + 1 );
	jumpState = 11;
	OOB = false;
}


__int8 Character::getRow( )
{
	return row;
}


__int8 Character::getIndex( )
{
	return index;
}


__int8 Character::getID( )
{
	return id;
}


bool Character::isOOB( )
{ 
	return OOB;
}


bool Character::isJumping( )
{
	return jumpState != 11;
}
