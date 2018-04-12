#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "platform.h"
#include "qbert.h"
#include "overlay.h"

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
	bool checkCollision( Character *c1, Character *c2 ); // Line 270
	void destroyCharacter( Character *c ); // Line 287

	bool addTimer( char *timerName, bool pauses );
	float checkTimer( char *timerName );
	void resetTimer( char *timerName );
	void removeTimer( char *timerName );


	enum State
	{
		startup = 0,
		title = 1,
		load = 2,
		game = 3,
		victory = 4,
		leaderboard = 5
	} state;

	typedef struct 
	{
		float time;
		char *name;
		bool pauses;
	} NamedTimer;

	// Temp
	__int8 flashChange;

	// GameObjects
	Platform platform;
	Qbert *q;
	std::vector< Character * > characters;
	bool respawning;
	Overlay overlay;

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
	std::vector< NamedTimer * > timers;
};
