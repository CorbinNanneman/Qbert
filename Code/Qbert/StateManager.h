#pragma once

#include <SFML/Graphics.hpp>
#include "TimerManager.h"
#include <vector>

#include "Platform.h"
#include "Qbert.h"

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
	StateManager( );

	bool isOpen( );
	void clear( );
	void update( );
	void display( );

	~StateManager( );

private:
	void startGame( );
	void clMem( );
	
	void checkEvents( );
	void stateUpdate( );
	void transitionState( State newState );

	void createOverlay( );
	void addOverlayEl( const char* texPath, __int16 texWidth, __int16 texHeight,
		__int16 x, __int16 y, __int8 tAFrames = 0, float aDelay = 0. );
	void clearOverlay( );

	bool checkCollision( Character *c1, Character *c2 );
	Character* createCharacter( __int8 characID );
	void destroyCharacter( Character *c );

	__int8 flashChange;
	
	// FPS Tracking
	__int8 targetFps;
	unsigned __int16 frame;
	float fps;
	float fpsScale;
	sf::Clock fpsClock;
	
	// Window
	__int16 screenWidth,
			screenHeight;
	float scale;
	sf::RenderWindow window;

	// Game Events
	unsigned __int8 pauseLevel;
	bool pauseKeyHeld;
	TimerManager timers;
	State state;

	// GameObjects
	Platform platform;
	Qbert *q = nullptr;
	std::vector< Character * > characters;
	std::vector< GameObject * > overlay;
	bool respawning;
	int score;
	__int8 player, level, round, lives;
	bool frozen;
};
