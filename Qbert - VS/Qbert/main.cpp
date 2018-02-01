/*
BLah blah
*/

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	double screenWidth = 800, 
		   screenHeight = screenWidth;

	sf::Texture t;
	t.loadFromFile("./images/blueBlue.png");
	// Map creation/allocation
	sf::Sprite **map = new sf::Sprite*[7];
	for (int i = 0; i < 7; i++)
		map[i] = new sf::Sprite[i + 1];

	// Map loopthrough
	int scale = 3, texWidth = 32 * scale;

	for (int row = 0; row < 7; row++)
	{
		for (int index = 0; index < row + 1; index++)
		{
			map[row][index].setTexture(t);
			map[row][index].setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(texWidth / scale, texWidth / scale)));
			// origin code here
			// Map coordinate calculations
			map[row][index].setScale(scale, scale);
			int x = row * texWidth * -.5 + index * texWidth + screenWidth / 2;
			// texWidth * (row * -.5 + index) + screenWidth / 2;
			int y = row * texWidth * .75 + 100;
			map[row][index].setPosition(x, y);
		}
	}

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

		window.clear(sf::Color::Black);

		for (int row = 0; row < 7; row++)
		{
			for (int index = 0; index < row + 1; index++)
				window.draw(map[row][index]);
		}

		window.display();
	}

	// Map deletion
	for (int i = 0; i < 7; i++)
		delete[] map[i];
	delete[] map;

	return 0;
}
