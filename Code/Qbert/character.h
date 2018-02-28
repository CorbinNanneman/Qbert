#pragma once
/*
Represents a character that moves between blocks.

Date Created:
	February 8th, 2018
Date Last Modified:
	February 8th, 2018 | 12:00 PM
*/

#include "gameObject.h"

class Character : public GameObject
{
public:
	Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth, 
		float jumpCD );

	virtual void update( float fpsScale, __int16 screenWidth, float scale, __int16 frame );

	void move( __int8 direction, float scale, float fpsScale );
	bool isOOB( );
	virtual void moveAnimate( __int8 direction ) = 0;

	~Character();
protected:
	float jumpTimer, jumpCDTime;
private:
	__int8 row, index, jumpDirection;
	bool OOB;
};
