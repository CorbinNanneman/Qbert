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
#include <vector>

#include <iostream>
#include "cube.h"
#include "platform.h"
#include "qbert.h"
#include "redball.h"
	
int main()
{
	srand( time( NULL ) );

	double screenWidth = 800, 
		   screenHeight = screenWidth;
	const __int8 targetFps = 60;

	// SFML Window
	sf::RenderWindow window( sf::VideoMode(screenWidth, screenHeight), "Q*bert" );

	float scale = 3;
	
	// FPS Tracking variables
	unsigned int frame = 0;
	__int16 fps = targetFps;
	float fpsScale = targetFps * 1.0 / fps;
	sf::Clock fpsTimer, spawnTimer;
	
	// Map/Character creation
	Platform platform;
	Qbert q( 0, 0, scale, screenWidth );
	std::vector<Character *> characters;

	// Platform initialization
	char* texStrings[3] = { "./images/blueBlue.png", NULL, "./images/blueTiedye1.png" };
	platform.createMap( texStrings, screenWidth, scale );
	
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
				q.move( 0, scale, fpsScale );
			else if( e.key.code == sf::Keyboard::C )
				q.move( 1, scale, fpsScale );
			else if( e.key.code == sf::Keyboard::Z )
				q.move( 2, scale, fpsScale );
			else if( e.key.code == sf::Keyboard::S )
				q.move( 3, scale, fpsScale );
		}

		window.clear(sf::Color::Black);

		// FPS Tracking (for game stabilization)
		frame++;
		if( fpsTimer.getElapsedTime( ).asMilliseconds( ) > 999 )
		{
			fps = frame;
			// Determines adjustment needed to match proper frame rate
			fpsScale = targetFps * 1.0 / fps;
			frame = 0;
			fpsTimer.restart( );
			std::cout << (int)fps << '\n';
		}

		// Spawns
		if( spawnTimer.getElapsedTime( ).asMilliseconds( ) > 1500 )
		{
			characters.push_back( new RedBall( scale, screenWidth, 0.75 ) );
			spawnTimer.restart( );
		}

		// Updates
		q.update( fpsScale, screenWidth, scale, frame );
		for( int i = 0; i < characters.size( ); i++ )
			characters.at( i )->update( fpsScale, screenWidth, scale, frame );

		// Draw behind map when OOB
		if( q.isOOB( ) )
			window.draw( *q.getSprite( ) );
		for( int i = 0; i < characters.size( ); i++ )
			if( characters.at( i )->isOOB( ) )
				window.draw( *characters.at( i )->getSprite( ) );
		

		// MAP DRAW
		Cube** map = platform.getCubes( );
		for( int row = 0; row < 7; row++ )
		{
			for( int index = 0; index < row + 1; index++ )
				window.draw( *map[row][index].getSprite( ) );
		}

		// Draw in front of map when in bounds
		if( !q.isOOB( ) )
			window.draw( *q.getSprite( ) );
		for( int i = 0; i < characters.size( ); i++ )
			if( !characters.at( i )->isOOB( ) )
				window.draw( *characters.at( i )->getSprite( ) );

		window.display( );
	}

	platform.deleteMap( );
	while( characters.size( ) > 0 )
	{
		delete characters.at( characters.size( ) - 1 );
		characters.pop_back( );
	}

	return 0;
}
