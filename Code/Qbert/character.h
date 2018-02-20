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
	Character( __int8 startRow, __int8 startIndex, __int8 scale, float screenWidth );

	void update( int frame );

	void move( __int8 direction, __int8 scale );
	void checkOOB( );

	~Character();
private:
	__int8 row, 
			index;
	unsigned int jumpTimer;
	bool isOOB;
};
