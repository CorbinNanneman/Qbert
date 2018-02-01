#include "platform.h"



Platform::Platform()
{
}


Platform::~Platform()
{
}


bool Platform::win()
{
	
}


void Platform::createMap(char* newTexStrings[3], double screenWidth, int scale)
{
	// Allocate map storage
	map = new Cube*[7];
	for (int i = 0; i < 7; i++)
		map[i] = new Cube[i + 1];

	for (int row = 0; row < 7; row++)
	{
		for (int index = 0; index < row + 1; index++)
		{
			// Set cube positions
			map[row][index].setTexture(texStrings[0]);
			map[row][index].getSprite().setTextureRect(sf::IntRect(sf::Vector2i(0, 0), 
				sf::Vector2i(32, 32)));
			map[row][index].getSprite().setOrigin(16, 16);
			// Map coordinate calculations
			map[row][index].getSprite().setScale(scale, scale);
			int x = 32 * (row * -.5 + index) + screenWidth / 2;
			// row * 32 * -.5 + index * 32 + screenWidth / 2;
			int y = row * 32 * .75 + 100;
			map[row][index].getSprite().setPosition(x, y);
		}
	}

	*texStrings = *newTexStrings;
}


void Platform::deleteMap()
{
	// Deallocate map storage
	for (int i = 0; i < 7; i++)
		delete[] map[i];
	delete[] map;
}
