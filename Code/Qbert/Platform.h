#pragma once

#include "Cube.h"
#include "Disk.h"

class Platform
{
public:
	Platform( );

	void createMap( char const *newTexStrings[ 3 ], __int16 screenWidth, float scale );
	void deleteMap( );

	Cube** getCubes( );
	void changeCube( __int8 row, __int8 index, __int8 changeType, __int8 level );
	bool isComplete( );

	~Platform();

private:
	std::vector<Disk*> disks;
	Cube** map;
	char const *texStrings[3]; // File paths for appropriate textures
	bool deleted = false;
};
