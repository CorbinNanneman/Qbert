/*==============================================================*\
|                                                                |
| Program: Qbert                                                 |
|                                                                |
| Breif: Classic arcade game recreated in C++                    |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| File: main.cpp                                                 |
|                                                                |
| Purpose: Drive the program without hosting any specific logic  |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| Author: Greg Francis                                           |
|                                                                |
| Date Created: February 12th, 2018                              |
|                                                                |
| Date Last Modified: Feburary 21th, 2018 | 7:32 PM              |
|                                                                |
\*==============================================================*/

#include <SFML/Graphics.hpp>

#include <iostream>
#include "cube.h"
#include "platform.h"
#include "character.h"
	
int main()
{
	double screenWidth = 800, 
		   screenHeight = screenWidth;

	// SFML Code
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Q*bert");
	window.setFramerateLimit( 60 );
	__int8 scale = 2;
	
	unsigned int frame = 0;
	
	Platform platform;
	Character q( 6, 0, scale, screenWidth );

	// Platform initialization
	char* texStrings[3] = { "./images/blueBlue.png", NULL, "./images/blueTiedye1.png" };
	platform.createMap(texStrings, screenWidth, scale);
	
	// Game Loop
	while ( window.isOpen( ) )
	{
		// EVENTS
		sf::Event e;
		while ( window.pollEvent( e ) )
		{
			if ( e.type == sf::Event::Closed )
				window.close();
			else if ( e.key.code == sf::Keyboard::Escape )
				window.close( );
			else if ( e.key.code == sf::Keyboard::D )
				q.move( 0, scale );
			else if( e.key.code == sf::Keyboard::C )
				q.move( 1, scale );
			else if( e.key.code == sf::Keyboard::Z )
				q.move( 2, scale );
			else if( e.key.code == sf::Keyboard::S )
				q.move( 3, scale );
		}

		window.clear(sf::Color::Black);

		frame = ( frame + 1 ) % 60; //Keeps frame cycling from 0 to 59
		q.update( frame );

		// MAP DRAW
		Cube** const &map = platform.getCubes( );
		for( int row = 0; row < 7; row++ )
		{
			for( int index = 0; index < row + 1; index++ )
				window.draw( *map[row][index].getSprite( ) );
		}

		window.draw( *q.getSprite( ) );

		window.display( );
	}

	platform.deleteMap( );

	return 0;
}
