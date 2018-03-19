#include "statemanager.h"
#include "redball.h"
#include "monkey.h"

#include <iostream>

StateManager::StateManager( )
{
	// FPS Tracking
	targetFps = 60;
	frame = 0;
	fps = targetFps;
	fpsScale = targetFps * 1.f / fps;

	// Window
	screenWidth = 800;
	screenHeight = screenWidth;
	scale = 3;
	window.create( sf::VideoMode( screenWidth, screenHeight ), "Q*Bert" );
	window.setFramerateLimit( 120 );

	addTimer( "delay", false );
}


StateManager::~StateManager( )
{
	delete q;
	platform.deleteMap( );
	while( characters.size( ) > 0 )
		destroyCharacter( characters.at( 0 ) );
	while( timers.size( ) > 0 )
		removeTimer( timers.at( 0 )->name );
}


void StateManager::startGame( )
{
	// Deallocate any old memory
	if( platform.getCubes( ) != nullptr )
		platform.deleteMap( );
	while( characters.size( ) > 0 )
		destroyCharacter( characters.at( 0 ) );
	while( timers.size( ) > 0 )
		removeTimer( timers.at( 0 )->name );

	// Objects
	q = new Qbert( scale, screenWidth );
	char* texStrings[ 3 ] = { "./images/blueBlue.png", "./images/bluePink.png", 
		"./images/blueYellow.png" };
	platform.createMap( texStrings, screenWidth, scale );

	// Data
	state = game;

	addTimer( "spawn", true );
	
	respawning = false;
	playing = true;
	paused = false;
	pauseKeyHeld = false;
}


// Reset all data to initial states
void StateManager::reset( )
{
	// Objects
	delete q;
	while( characters.size( ) != 0 )
		destroyCharacter( characters.at( 0 ) );
	platform.deleteMap( );

	// Timers
	while( timers.size( ) > 0 )
		removeTimer( timers.at( 0 )->name );

	startGame( );
}


bool StateManager::isOpen( )
{
	return window.isOpen( );
}


void StateManager::clear( )
{
	window.clear( sf::Color::Black );
}


void StateManager::update( )
{
	// FPS Tracking
	frame++;
	if( fpsClock.getElapsedTime( ).asMilliseconds( ) > 999 )
	{
		fps = frame;
		// Determines adjustment needed to match proper frame rate
		fpsScale = targetFps * 1.f / fps;
		frame = 0;
		fpsClock.restart( );
	}

	// Timer updates
	for( unsigned __int8 i = 0; i < timers.size( ); i++ )
		if( !paused || !timers.at( i )->pauses )
			timers.at( i )->time += 1.f / fps;

	// Delay Logic. Only true when window is loading.
	if( !playing )
	{
		if( checkTimer( "delay" ) > 2.f )
		{
			playing = true;
			removeTimer( "delay" );
			startGame( );
		}
	}
	else
	{
		checkEvents( );
		stateUpdate( );
	}
}


void StateManager::display( )
{
	if( playing )
	{
		// Tracks characters in front of map
		std::vector< Character * > inFront;

		// Draw characters behind map when OOB
		if( q->isOOB( ) )
			window.draw( *q->getSprite( ) );
		else
			inFront.push_back( q );
		for( __int8 i = 0; i < characters.size( ); i++ )
		{
			if( characters.at( i )->isOOB( ) )
				window.draw( *characters.at( i )->getSprite( ) );
			else
				inFront.push_back( characters.at( i ) );
		}

		// MAP DRAW
		Cube** map = platform.getCubes( );
		for( int row = 0; row < 7; row++ )
		{
			for( int index = 0; index < row + 1; index++ )
				window.draw( *map[ row ][ index ].getSprite( ) );
		}

		// Draw characters in front of map when in bounds
		for( __int8 i = 0; i < inFront.size( ); i++ )
			window.draw( *inFront.at( i )->getSprite( ) );
	}

	window.display( );
}


void StateManager::checkEvents( )
{
	sf::Event e;
	while( window.pollEvent( e ) )
	{
		switch( e.type )
		{
		case sf::Event::Closed:
			window.close( );
			break;
		case sf::Event::LostFocus:
			paused = true;
			break;
			// KeyBoard Input
		case sf::Event::KeyPressed:
			switch( e.key.code )
			{
			case sf::Keyboard::Escape:
				window.close( );
				break;
			case sf::Keyboard::D:
				if( !paused )
					q->move( 0, scale, fpsScale );
				break;
			case sf::Keyboard::C:
				if( !paused )
					q->move( 1, scale, fpsScale );
				break;
			case sf::Keyboard::Z:
				if( !paused )
					q->move( 2, scale, fpsScale );
				break;
			case sf::Keyboard::S:
				if( !paused )
					q->move( 3, scale, fpsScale );
				break;
			case sf::Keyboard::P:
				if( !pauseKeyHeld )
					paused = !paused;
				pauseKeyHeld = true;
				break;
			default:
				break;
			}
			break;
		}
	}
	// Update status of pause key when no longer held
	if( pauseKeyHeld )
		if( !sf::Keyboard::isKeyPressed( sf::Keyboard::P ) )
			pauseKeyHeld = false;
}


void StateManager::stateUpdate( )
{
	__int8 qReturn;
	switch( state )
	{
	case game:
		if( !paused )
		{
			// Spawns
			if( checkTimer( "spawn" ) > 2.5f )
			{
				if( rand( ) % 2 == 0 )
					characters.push_back( new RedBall( scale, screenWidth, 1.25 ) );
				else
					characters.push_back( new Monkey( scale, screenWidth, 1.25 ) );
				resetTimer( "spawn" );
			}
			// Q*Bert update
			qReturn = q->update( fpsScale, screenWidth, scale, frame );
			switch( qReturn )
			{
			default:
			case 0:
				break;
			case 1: // Q*Bert is jumping
				// Collision Check
				for( unsigned int i = 0; i < characters.size( ); i++ )
				{
					if( checkCollision( q, characters.at( i ) ) )
					{
						paused = true;
						respawning = true;
						addTimer( "respawn", false );
					}
				} // end loop - character collision checking
				break;
			case 2: // Q*Bert completed jump
				platform.changeCube( q->getRow( ), q->getIndex( ), 0, 1 );

				if( platform.isComplete( ) )
				{
					state = victory;
					addTimer( "flash", true );
					flashChange = 0;
				}
				break;
			case 3: // Q*Bert fell off world
				q->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
				break;
			} // end switch - qReturn

			  // Characters updates
			for( unsigned __int8 i = 0; i < characters.size( ); i++ )
			{
				__int8 charReturn = characters.at( i )->update( fpsScale, screenWidth, scale, frame );
				switch( charReturn )
				{
				default:
				case 0:
				case 1: // Character is jumping
					if( qReturn != 1 && checkCollision( characters.at( i ), q ) )
					{
						paused = true;
						respawning = true;
						addTimer( "respawn", false );
					}
					break;
				case 2: // Character completes jump
					break;
				case 3: // Character fell off world
					destroyCharacter( characters.at( i ) );
					break;
				} // endswitch - character return
			} // endfor - character vector loop
		} // endif - !paused
		else if( respawning )
		{
			if( checkTimer( "respawn" ) > 2.f )
			{
				removeTimer( "respawn" );

				startGame( );
			}
		}
		break;

	case victory:
		// Flash cubes 9 times
		if( checkTimer( "flash" ) > 0.1f )
		{
			for( int row = 0; row < 7; row++ )
				for( int index = 0; index < row + 1; index++ )
					platform.changeCube( row, index, 0, 5 );
			resetTimer( "flash" );

			if( ++flashChange > 14 )
			{
				removeTimer( "flash" );

				startGame( );
			}
		}
		break;

	default:
		break;
	}
}


bool StateManager::checkCollision( Character *c1, Character *c2 )
{
	bool collision = false;
	
	if( !c1->isOOB( ) && !c2->isOOB( ) )
	{
		int xDist = c1->getX( ) - c2->getX( ),
			yDist = c1->getY( ) - c2->getY( ),
			boundsFactor = 8 * scale;
		if( xDist > -boundsFactor && xDist < boundsFactor && yDist > -boundsFactor && 
			yDist < boundsFactor )
			collision = true;
	}
	return collision;
}


void StateManager::destroyCharacter( Character *c )
{
	bool deleted = false;
	for( int i = 0; !deleted && i < characters.size( ); i++ )
	{
		if( c == characters.at( i ) )
		{
			delete c;
			characters.erase( characters.begin( ) + i );
			deleted = true;
		}
	}
}


void StateManager::addTimer( char *timerName, bool pauses )
{
	// Create Timer if not already created
	if( checkTimer( timerName ) == -1.f )
	{
		NamedTimer *t = new NamedTimer;
		t->name = timerName;
		t->time = 0.f;
		t->pauses = pauses;
		timers.push_back( t );
	}
}


float StateManager::checkTimer( char *timerName )
{
	float time = -1.f; // If this is returned the timer does not exist

	for( __int8 i = 0; time == -1.f && i < timers.size( ); i++ )
		if( timers.at( i )->name == timerName )
			time = timers.at( i )->time;

	return time;
}


void StateManager::resetTimer( char *timerName )
{
	bool reset = false;
	for( __int8 i = 0; !reset && i < timers.size( ); i++ )
	{
		if( timers.at( i )->name == timerName )
		{
			timers.at( i )->time = 0.f;
			reset = true;
		}
	}
}


void StateManager::removeTimer( char *timerName )
{ 
	bool removed = false;
	for( int i = 0; !removed && i < timers.size( ); i++ )
	{
		if( timers.at( i )->name == timerName );
		{
			delete timers.at( i );
			timers.erase( timers.begin( ) + i );
			removed = true;
		}
	}
}
