/*
BLah blah
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cube.h"
#include "platform.h"

int main()
{
	double screenWidth = 800, 
		   screenHeight = screenWidth;

	// SFML Code
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Cubert");
	int scale = 2;
	
	Platform platform;

	char* texStrings[3] = { "./images/blueBlue.png", NULL, "./images/blueTiedye1.png" };
	platform.createMap(texStrings, screenWidth, scale);
	
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		Cube** map = platform.getCubes();
		for (int row = 0; row < 7; row++)
		{
			for (int index = 0; index < row + 1; index++)
				window.draw(*(map[row][index].getSprite()));
		}

		window.display();
	}

	platform.deleteMap();

	return 0;
}
