#include "platform.h"

#include <iostream>

Platform::Platform()
{
}


Platform::~Platform()
{
}


bool Platform::win()
{
	return false;
}


Cube** Platform::getCubes()
{
	return map;
}


// When only 2 cube textures are needed, newTexStrings[1] is set to NULL
void Platform::createMap(char* newTexStrings[3], double screenWidth, int scale)
{
	*texStrings = *newTexStrings;

	// Allocate map storage
	map = new Cube*[7];
	for (int i = 0; i < 7; i++)
		map[i] = new Cube[i + 1];

	// Initialize and position cubes in map
	for (int row = 0; row < 7; row++)
	{
		for (int index = 0; index < row + 1; index++)
		{
			// Initialize textures
			map[row][index].setTexture(texStrings[0], 32, 32);
			map[row][index].getSprite()->setOrigin(16, 16);

			// Map coordinate calculations
			map[row][index].getSprite()->setScale(scale, scale);
			int x = 32 * scale * (row * -.5 + index) + screenWidth / 2;
			int y = row * scale * 32 * .75 + 100;

			map[row][index].setX(x);
			map[row][index].setY(y);
			map[row][index].update(NULL);
		}
	}
}


void Platform::deleteMap()
{
	// Deallocate map storage
	for (int i = 0; i < 7; i++)
		delete[] map[i];
	delete[] map;
}
