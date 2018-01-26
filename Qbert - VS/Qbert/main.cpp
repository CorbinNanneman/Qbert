/*
BLah blah
*/

#include <SFML/Graphics.hpp>

int main()
{
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