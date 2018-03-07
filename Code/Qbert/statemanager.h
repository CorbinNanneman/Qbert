#pragma once
/*==============================================================*\
|                                                                |
| Program: Qbert                                                 |
|                                                                |
| Breif: Classic arcade game recreated in C++                    |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| Class: StateManager                                            |
|                                                                |
| Purpose: Manage all objects and perfrom state-based logic      |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| Author: Greg Francis                                           |
|                                                                |
| Date Last Updated: Feburary 21th, 2018 | 7:32 PM               |
|                                                                |
\*==============================================================*/

#include <SFML/Graphics.hpp>
#include <vector>

#include "platform.h"
#include "qbert.h"

class StateManager
{
public:
	StateManager( ); // Line

	bool isOpen( ); // Line
	void clear( ); // Line
	void update( ); // Line
	void display( ); // Line

	~StateManager( );

private:
	void destroyCharacter( Character *c ); // Line 180 or somethin
	bool checkCollision( Character *c1, Character *c2 ); // Line 190

	// GameObjects
	Platform platform;
	Qbert *q;
	std::vector<Character *> characters;

	// FPS Tracking
	__int8 targetFps = 60;
	unsigned __int16 frame = 0,
					 fps = targetFps;
	float fpsScale = targetFps * 1.f / fps;
	sf::Clock fpsTimer;

	// Window
	sf::RenderWindow window;
	__int16 screenWidth,
		screenHeight;
	float scale;
	sf::Clock gameTimer,
			  spawnTimer;

	enum State
	{
		startup = 0,
		title = 1,
		load = 2,
		game = 3,
		leaderboard = 4
	} state;
};