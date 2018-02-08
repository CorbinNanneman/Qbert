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
	Platform();

	bool win();
	Cube** getCubes();

	void createMap(char* newTexStrings[3], double screenWidth, int scale);
	void deleteMap();

	~Platform();
private:
	char* texStrings[3]; // File paths for appropriate textures
	Cube **map;
};
