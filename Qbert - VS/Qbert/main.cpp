/*

Program: Qbert

Breif: Classic arcade game recreated in C++

------------------------------------------------------------------------

File: main.cpp

Purpose: Drive the program without performing any of the main logic

------------------------------------------------------------------------

Author: Greg Francis

Date Created: February 12th, 2018

Date Last Modified: Feburary 12th, 2018 | 12:57 PM

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

	// Platform initialization
	char* texStrings[3] = { "./images/blueBlue.png", NULL, "./images/blueTiedye1.png" };
	platform.createMap(texStrings, screenWidth, scale);
	
	while (window.isOpen())
	{
		// EVENTS
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		// MAP DRAW
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
