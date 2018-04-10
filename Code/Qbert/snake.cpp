#include "Snake.h"
#include "time.h"
#include <iostream>

Snake::Snake(float scale, __int16 screenWidth, float jumpCD)
	: Character(1, rand() % 2, scale, screenWidth, jumpCD)
{
	isEgg = true;
	setTexture("./images/snakeEgg.png", 16, 16);
	setTexRect( 1, 0 );

	setY( -14 * scale );
	jumpState = 4;
	id = 1;
}


Snake::~Snake( )
{ }


__int8 Snake::update(float fpsScale, __int16 screenWidth, float scale)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale);

	if (isEgg)
	{
		if( getRow( ) == 6 )
		{
			setTexture( "./images/snake.png", 16, 32 );
			isEgg = false;
		}
		else if (jumpTimer > jumpCDTime)
			Character::move(rand() % 2 + 1, scale, fpsScale);
	}
	// Hatched snake movement AI
	else
	{   
		// Target above snake
		if (targetRow < getRow())
		{
			if (targetX == getX())
				Character::move(rand() % 2 * 3, scale, fpsScale);
			else if (targetX > getX())
				Character::move(0, scale, fpsScale);
			else
				Character::move(3, scale, fpsScale);
		}
		// Target below snake
		else if (targetRow > getRow())
		{
			if (targetX == getX())
				Character::move(rand() % 2 + 1, scale, fpsScale);
			else if (targetX > getX())
				Character::move(1, scale, fpsScale);
			else
				Character::move(2, scale, fpsScale);
		}
		// Target on same row as snake
		else
		{
			if (getRow() == 6)
			{
				if (targetX > getX())
					Character::move(0, scale, fpsScale);
				else
					Character::move(3, scale, fpsScale);
			}
			else
			{
				if (targetX > GameObject::getX())
					Character::move(rand() % 2, scale, fpsScale);
				else
					Character::move(rand() % 2 + 2, scale, fpsScale);
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


void Snake::findTarget( Qbert &q, __int8 qReturn )
{
	static __int8 lastQRet = 0;
	//if( lastQRet )
	switch( qReturn )
	{
	default:
	case 0: // Qbert idling
	case 2: // Qbert completing jump
		targetX = q.getX( );
		targetRow = q.getRow( );
		break;
	case 1: // Qbert jumping
		if( !q.isOOB( ) )
		{
			targetX = q.getTX( );
			targetRow = q.getTRow( );
			break;
		}
	case 3: // Qbert fell out of bounds
		// Snake at Qberts last block
		if( getX( ) == q.getLX( ) && getRow( ) == q.getLRow( ) )
		{
			targetX = q.getTX( );
			targetRow = q.getTRow( );
		}
		else 
		{
			targetX = q.getLX( );
			targetRow = q.getLRow( );
		}
		break;
	}
	lastQRet = qReturn;
}
