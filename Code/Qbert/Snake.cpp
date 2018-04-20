#include "Snake.h"
#include "time.h"

Snake::Snake(float scale, __int16 screenWidth, float jumpCD, Qbert *q)
	: Character(1, rand() % 2, scale, screenWidth, jumpCD)
{
	isEgg = true;
	setTexture("./images/snakeEgg.png", 16, 16);
	setTexRect( 1, 0 );

	setY( -14 * scale );
	jumpState = 4;
	id = 1;
	qbert = q;
}


Snake::~Snake( )
{ }

__int8 Snake::update(float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale);

	if (isEgg)
	{
		if( retVal == 2 && getRow( ) == 6 )
		{
			setTexture( "./images/snake.png", 16, 32 );
			isEgg = false;
		}
		else if (jumpTimer > jumpCDTime)
			Character::move(rand() % 2 + 1, scale * fpsScale);
	}
	// Hatched snake movement AI
	else if( retVal == 0 || retVal == 2 )
	{
		findTarget( );
		// Target above snake
		if ( targetY < getY())
		{
			if (targetX == getX())
				move(rand() % 2 * 3, scale * fpsScale);
			else if (targetX > getX())
				move(0, scale * fpsScale);
			else
				move(3, scale * fpsScale);
		}
		// Target below snake
		else if ( targetY > getY())
		{
			if (targetX == getX())
				move(rand() % 2 + 1, scale * fpsScale);
			else if (targetX > getX())
				move(1, scale * fpsScale);
			else
				move(2, scale * fpsScale);
		}
		// Target on same row as snake
		else
		{
			// Target not on bottom row
			if (getRow() != 6 )
			{
				// Target is right of qbert
				if( targetX > getX( ) )
				{
					// Actual qbert target y above snake y
					if( qbert->getTY( ) < getY( ) )
						move( 0, scale * fpsScale );
					// Actual qbert target y below snake y
					else if( qbert->getTY( ) > getY( ) )
						move( 1, scale * fpsScale );
					// Actual qbert target y equal to snake y
					else
						move( rand( ) % 2, scale * fpsScale );
				}
				// Target is left of qbert
				else
				{
					// Actual qbert target y above snake y
					if( qbert->getTY( ) < getY( ) )
						move( 3, scale * fpsScale );
					// Actual qbert target y below snake y
					else if( qbert->getTY( ) > getY( ) )
						move( 2, scale * fpsScale );
					// Actual qbert target y equal to snake y
					else
						move( rand( ) % 2 + 2, scale * fpsScale );
				}
			}
			// Target on bottom row
			else
			{
				if( targetX > getX( ) )
					move( 0, scale * fpsScale );
				else
					move( 3, scale * fpsScale );
			}	
		}
	}
	return retVal;
}


void Snake::moveAnimate(__int8 state)
{
	if (isEgg)
	{
		if (state < 4)
			setTexRect( 1, 0 );
		else
			setTexRect( 0, 0 );
	}
	else
	{
		switch (state)
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
}

void Snake::findTarget( )
{
	if( !qbert->isOOB( ) && !qbert->isJumping( ) )
	{
		targetX = qbert->getX( );
		targetY = qbert->getY( );
	}
	else
	{
		// If Snake isn't on Q's last pos
		if( getX( ) != qbert->getLX( ) || getY( ) != qbert->getLY( ) )
		{
			targetX = qbert->getLX( );
			targetY = qbert->getLY( );
		}
		else // Jump Off
		{
			targetX = qbert->getTX( );
			targetY = qbert->getTY( );
		}
	}
}
