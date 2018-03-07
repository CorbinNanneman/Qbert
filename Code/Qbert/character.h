#pragma once
/*
Represents a character that moves between blocks.

Date Created:
	February 8th, 2018
Date Last Modified:
	February 8th, 2018 | 12:00 PM
*/

#include "gameobject.h"

class Character : public GameObject
{
public:
	Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth, 
		float jumpCD );

	virtual __int8 update( float fpsScale, __int16 screenWidth, float scale, __int16 frame );

	void move( __int8 direction, float scale, float fpsScale );
	void die( );
	virtual void moveAnimate( __int8 direction ) = 0;

	__int8 getRow( );
	__int8 getIndex( );
	__int8 getDirection( );
	bool isOOB( );
	bool isJumping( );

	~Character();

protected:
	__int8 jumpDirection;
	float jumpTimer, jumpCDTime;
	
private:
	__int8 row, 
		   index;

	bool OOB;
};
