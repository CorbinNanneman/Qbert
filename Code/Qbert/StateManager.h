#pragma once

#include <SFML/Graphics.hpp>
#include "TimerManager.h"
#include <vector>

#include "Platform.h"
#include "Qbert.h"
#include "Overlay.h"
#include "Disk.h"

enum State
{
	startup = 0,
	title = 1,
	load = 2,
	game = 3,
	victory = 4,
	leaderboard = 5
};

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
	void transitionState( State newState );

	void createOverlay( );
	void addOverlayEl( const char* texPath, __int16 texWidth, __int16 texHeight,
		__int16 x, __int16 y, __int8 tAFrames = 0, float aDelay = 0. );
	void clearOverlay( );

	bool checkCollision( Character *c1, Character *c2 ); // Line 270
	Character* createCharacter( __int8 characID );
	void destroyCharacter( Character *c ); // Line 287

	// Temp
	__int8 flashChange;
	__int8 player, level;

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
	State state;

	// GameObjects
	Platform platform;
	Qbert *q = nullptr;
	std::vector< Character * > characters;
	std::vector< GameObject * > overlay;
	bool respawning;
	int score;
	__int8 lives;
};
