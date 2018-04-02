#pragma once

#include "cube.h"

class Platform
{
public:
	Platform( );

	void createMap( char* newTexStrings[ 3 ], __int16 screenWidth, float scale );
	void deleteMap( );

	Cube** getCubes( );
	void changeCube( __int8 row, __int8 index, __int8 changeType, __int8 level );
	bool isComplete( );

	~Platform();

private:
	Cube** map;
	char* texStrings[3]; // File paths for appropriate textures
	bool deleted = false;
};
