#include "Snake.h"
#include "time.h"

Snake::Snake(float scale, __int16 screenWidth, float jumpCD, Qbert *q)
	: Character(1, rand() % 2, scale, screenWidth, jumpCD)
{
	isEgg = true;
	setTexture("./images/snakeEgg.png", 16, 13);
	setTexRect( 1, 0 );

	setY( -14 * scale );
	setYOffset( 3 * scale );

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
			setYOffset( -3 * scale );
			// Re-set position for offset
			setX( 32 * scale * ( getRow( ) * -.5f + getIndex( ) ) + screenWidth / 2 );
			setY( scale * ( getRow( ) * 24 + 34 ) );
			isEgg = false;
		}
		else if (jumpTimer > jumpCDTime)
			Character::move(rand() % 2 + 1, scale );
	}
	// Hatched snake movement AI
	else if( retVal == 0 || retVal == 2 )
	{
		findTarget( );
		// Target above snake
		if ( targetY < getY( ) - getYOffset( ) )
		{
			if (targetX == getX())
				move(rand( ) % 2 * 3, scale );
			else if (targetX > getX( ) )
				move(0, scale );
			else
				move(3, scale );
		}
		// Target below snake
		else if ( targetY > getY( ) - getYOffset( ) )
		{
			if (targetX == getX())
				move(rand() % 2 + 1, scale );
			else if (targetX > getX())
				move(1, scale );
			else
				move(2, scale );
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
					if( qbert->getTY( ) < getY( ) - getYOffset( ) )
						move( 0, scale );
					// Actual qbert target y below snake y
					else if( qbert->getTY( ) > getY( ) - getYOffset( ) )
						move( 1, scale );
					// Actual qbert target y equal to snake y
					else
						move( rand( ) % 2, scale );
				}
				// Target is left of qbert
				else
				{
					// Actual qbert target y above snake y
					if( qbert->getTY( ) < getY( ) - getYOffset( ) )
						move( 3, scale );
					// Actual qbert target y below snake y
					else if( qbert->getTY( ) > getY( ) - getYOffset( ) )
						move( 2, scale );
					// Actual qbert target y equal to snake y
					else
						move( rand( ) % 2 + 2, scale );
				}
			}
			// Snake/target are on bottom row
			else
			{
				if( targetX > getX( ) )
					move( 0, scale );
				else if( targetX < getX( ) )
					move( 3, scale );
				// Snake is on target position
				else
				{
					// Qbert actually right of snake
					if( getX( ) > qbert->getX( ) )
					{
						if( qbert->getTY( ) < getY( ) - getYOffset( ) )
							move( 0, scale );
						else
							move( 1, scale );
					}
					// Qbert actually left of snake
					else
					{
						if( qbert->getTY( ) < getY( ) - getYOffset( ) )
							move( 3, scale );
						else
							move( 2, scale );
					}

				}

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
		if( getX( ) - getXOffset( ) != qbert->getLX( ) || getY( ) - getYOffset( ) != qbert->getLY( ) )
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
