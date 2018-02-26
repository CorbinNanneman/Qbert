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
	Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth );

	void update( int frame, __int8 fps, __int16 screenWidth, float scale );

	void move( __int8 direction, float scale, __int8 fps );
	bool isOOB( );
	virtual void moveAnimate( __int8 direction ) = 0;

	~Character();
private:
	__int8 row, index, jumpDirection;
	unsigned int jumpTimer;
	bool OOB;
};
