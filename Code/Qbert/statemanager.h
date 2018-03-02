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

#include "cube.h"
#include "platform.h"
#include "qbert.h"
#include "redball.h"

class StateManager
{
public:
	StateManager( );

	bool isOpen( );
	void clear( );
	void update( );
	void display( );

	~StateManager( );

private:
	// GameObjects
	Platform platform;
	Qbert *q;
	std::vector<Character *> characters;

	// FPS Tracking
	__int8 targetFps = 60;
	unsigned __int16 frame = 0,
					 fps = targetFps;
	float fpsScale = targetFps * 1.f / fps;
	sf::Clock fpsTimer, spawnTimer;

	// Window
	sf::RenderWindow window;
	__int16 screenWidth,
		screenHeight;
	float scale;

	enum State
	{
		startup = 0,
		title = 1,
		load = 2,
		game = 3,
		leaderboard = 4
	} state;
};