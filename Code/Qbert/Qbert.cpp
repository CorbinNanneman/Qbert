#include "Qbert.h"

Qbert::Qbert( float scale = 0, __int16 screenWidth = 0 )
	: Character( 0, 0, scale, screenWidth, 0.5 )
{ 
	setTexture( "./images/Qbert.png", 16, 16 );
	setTexRect( 4, 0 );

	jumpState = 11;
	id = 0;
	spinning = false;
}


Qbert::~Qbert( )
{ }


__int8 Qbert::update(float fpsScale, __int16 screenWidth, float scale, bool diskbound, float fps)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale);
	if (diskbound && jumpTimer > 0.5f)
	{
		spinning = true;
		retVal = 2;
		setZ(1);
	}

	if (spinning)
	{
		spinTimer += 1.f / fps;
		if (spinTimer > 0.2f)
		{
			static __int8 rotJumpState = jumpState + 4;
			if (++rotJumpState == 8)
				rotJumpState = 4;
			moveAnimate(rotJumpState);

			spinTimer = 0.f;
		}
	}

	return retVal;
}


void Qbert::move( __int8 direction, float scale, float fpsScale )
{
	Character::move( direction, scale * fpsScale );
	lastY = getY( );
	lastX = getX( );

	switch( direction )
	{
	case 0: // Up right
		targetX = getX( ) + 16 * scale;
		targetY = getY( ) - 24 * scale;
		break;
	case 1: // Down right
		targetX = getX( ) + 16 * scale;
		targetY = getY( ) + 24 * scale;
	case 2: // Down left
		targetX = getX( ) - 16 * scale;
		targetY = getY( ) + 24 * scale;
		break;
	case 3: // Up left
		targetX = getX( ) - 16 * scale;
		targetY = getY( ) - 24 * scale;
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


float Qbert::getTX( )
{
	return targetX;
}


float Qbert::getTY( )
{
	return targetY;
}


float Qbert::getLX( )
{
	return lastX;
}


float Qbert::getLY( )
{
	return lastY;
}


bool Qbert::isSpinning()
{
	return spinning;
}
