/*
BLah blah
*/

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	// Map creation/allocation
	char **map = new char*[7];
	for (int i = 0; i < 7; i++)
		map[i] = new char[i + 1];

	// Map loopthrough
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			map[i][j] = '0';
			std::cout << map[i][j];
		}
		std::cout << '\n';
	}

	// Map deletion
	for (int i = 0; i < 7; i++)
		delete[] map[i];
	delete[] map;

	system( "PAUSE" );

	int x, y, screenWidth, texWidth;
	// Map drawing (assume textures are centered
	for (int row = 0; row < 7; row++)
	{
		for (int index = 0; index < row + 1; index++)
		{
			x = row * texWidth * -.5 + index * texWidth + screenWidth / 2;
			texWidth * (row * -.5 + index) + screenWidth / 2;
			y = row * texWidth * .75 + 100;
		}
	}

	system( "PAUSE" );

	// SFML Code
	sf::RenderWindow window(sf::VideoMode(800, 800), "Cubert");

	sf::CircleShape c(100.0f);
	c.setFillColor(sf::Color::Magenta);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Green);

		window.draw(c);

		window.display();
	}

	return 0;
}
