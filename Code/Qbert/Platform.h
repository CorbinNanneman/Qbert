#pragma once

#include "Cube.h"
#include "Disk.h"

class Platform
{
public:
	Platform( );

	void createMap( __int8 level, __int8 round, __int16 screenWidth, float scale );
	void deleteMap( );

	void changeCube( __int8 row, __int8 index, __int8 changeType, __int8 level );
	bool isComplete( );

	Cube** getCubes( );
	std::vector<Disk*> Platform::getDisks( );

	~Platform();

private:
	void setTextures( __int8 level, __int8 round );

	Cube** map;
	std::vector<Disk*> disks;
	char const *texStrings[3]; // File paths for appropriate textures
};
