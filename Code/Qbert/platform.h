#pragma once
/*
Date Created:
Feburary 1st, 2018
Date Last Modified:
Feburary 1st, 2018 | 12:04PM
*/

#include "cube.h"

class Platform
{
public:
	Platform( );

	void createMap( char* newTexStrings[ 3 ], double screenWidth, int scale );
	void deleteMap( );

	Cube** getCubes( );
	void changeCube( __int8 row, __int8 index, __int8 changeType, __int8 level );

	bool win( );

	~Platform();

private:
	Cube** map;
	char* texStrings[3]; // File paths for appropriate textures
};
