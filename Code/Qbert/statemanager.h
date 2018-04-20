#pragma once

#include <SFML/Graphics.hpp>
#include "TimerManager.h"
#include <vector>

#include "Platform.h"
#include "Qbert.h"
#include "Overlay.h"

class StateManager
{
public:
	StateManager( ); // Line 6

	bool isOpen( ); // Line 65
	void clear( ); // Line 71
	void update( ); // Line 127
	void display( ); // Line 242

	~StateManager( ); // Line 25

private:
	void startGame( ); // Line 32
	void reset( ); // Line 49
	
	void checkEvents( ); // Line 77
	void stateUpdate( );
	void transitionState( __int8 newState );

	bool checkCollision( Character *c1, Character *c2 ); // Line 270
	Character* createCharacter( __int8 characID );
	void destroyCharacter( Character *c ); // Line 287

	enum State
	{
		startup = 0,
		title = 1,
		load = 2,
		game = 3,
		victory = 4,
		leaderboard = 5
	} state;

	// Temp
	__int8 flashChange;

	// FPS Tracking
	__int8 targetFps = 60;
	unsigned __int16 frame = 0,
					 fps = targetFps;
	float fpsScale = targetFps * 1.f / fps;
	sf::Clock fpsClock;
	
	// Window
	__int16 screenWidth,
			screenHeight;
	float scale;
	sf::RenderWindow window;

	// Game Events
	bool paused, 
		 pauseKeyHeld,
		 windowLoaded;
	TimerManager timers;

	// GameObjects
	Platform platform;
	Qbert *q = nullptr;
	std::vector< Character * > characters;
	bool respawning;
	Overlay overlay;
	int score;
	__int8 lives;
};
