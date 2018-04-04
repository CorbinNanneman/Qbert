#include "statemanager.h"
#include "redball.h"
#include "monkey.h"
#include "snake.h"
#include "lankyDude.h"

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
	characters.push_back( q );
	char* texStrings[ 3 ] = { "./images/blueBlue.png", "./images/bluePink.png", 
		"./images/blueYellow.png" };
	platform.createMap( texStrings, screenWidth, scale );

	// Data
	state = game;

	addTimer( "snakeSpawn", true );
	
	respawning = false;
	playing = true;
	paused = false;
	pauseKeyHeld = false;

	overlay.createObjects( 1, 3, 0, 0, 0, scale );
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

	// Delay Logic. Only relevant when window is loading.
	if( !playing )
	{
		if( checkTimer( "delay" ) > 5.f )
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
		std::vector< Character * > frontChars;

		// Draw characters that are behind map
		for( __int8 i = 0; i < characters.size( ); i++ )
		{
			switch( characters.at( i )->getID( ) )
			{
			default:
				if( characters.at( i )->isOOB( ) )
				{
					window.draw( *characters.at( i )->getSpritePtr( ) );
					break;
				}
			case 2:
			case 3:
				frontChars.push_back( characters.at( i ) );
				break;
			}
		}

		// Draw map
		Cube** map = platform.getCubes( );
		for( int row = 0; row < 7; row++ )
		{
			for( int index = 0; index < row + 1; index++ )
				window.draw( *map[ row ][ index ].getSpritePtr( ) );
		}

		// Draw characters that are in front of map
		for( __int8 i = 0; i < frontChars.size( ); i++ )
			window.draw( *frontChars.at( i )->getSpritePtr( ) );

		// Draw overlay
		std::vector< GameObject * > &elements = overlay.getElements( );
		for( int i = 0; i < elements.size( ); i++ )
			window.draw( *elements.at( i )->getSpritePtr( ) );
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

		case sf::Event::KeyPressed:
			switch( e.key.code )
			{
			case sf::Keyboard::Escape:
				window.close( );
				break;
			case sf::Keyboard::D:
				if( state == game && !paused )
					q->move( 0, scale, fpsScale );
				break;
			case sf::Keyboard::C:
				if( state == game && !paused )
					q->move( 1, scale, fpsScale );
				break;
			case sf::Keyboard::Z:
				if( state == game && !paused )
					q->move( 2, scale, fpsScale );
				break;
			case sf::Keyboard::S:
				if( state == game && !paused )
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


/* Character IDs
 0 - Qbert
 1 - Snake
 2 - Monkey
 3 - Lanky Dude
 4 - Red Ball
 5 - Magic Ball
 6 - Slick
 7 - Sam
*/
void StateManager::stateUpdate( )
{
	
	switch( state )
	{
// Game
	case game:
		if( !paused )
		{

	// Spawns
			if( checkTimer( "snakeSpawn" ) > 0.2f )
			{
				characters.push_back( new Snake( scale, screenWidth, 1.0f ) );
				removeTimer( "snakeSpawn" );
				addTimer( "spawn", true );
			}
			if( checkTimer( "spawn" ) > 4.3f )
			{
				if( rand( ) % 2 == 0 )
					characters.push_back( new RedBall( scale, screenWidth, 1.1f ) );
				else
					characters.push_back( new Monkey( scale, screenWidth, 1.25f ) );
				resetTimer( "spawn" );
			}

	// Character updates
			__int8 qReturn;
			for( unsigned __int8 i = 0; i < characters.size( ); i++ )
			{
				// Shortened character handle
				Character *curChar = characters.at( i );

				__int8 charReturn = curChar->update( fpsScale, screenWidth, scale);
				if( curChar == q )
					qReturn = charReturn;

				switch( charReturn )
				{
				default:
				case 0: // Character does nothing
					break;
				case 1: // Character is jumping
					// NEED QBERT COLLISION
					if( curChar != q && checkCollision( curChar, q ) )
					{
						if( curChar->getID( ) < 5 )
						{
							paused = true;
							respawning = true;
							addTimer( "respawn", false );
						}
						else
							destroyCharacter( curChar );
					}
					break;
				case 2: // Character completes jump
					switch( curChar->getID( ) )
					{
					case 0: // Qbert
						platform.changeCube( q->getRow( ), q->getIndex( ), 0, 1 );

						if( platform.isComplete( ) )
						{
							state = victory;
							addTimer( "flash", true );
							flashChange = 0;
						}
						break;
					case 1: // Snake
						dynamic_cast< Snake* >( characters.at( i ) )->setTarget(
							q->getX( ), q->getRow( ) );
					default:
						break;
					}
					break;
				case 3: // Character fell off world
					destroyCharacter( characters.at( i ) );
					break;
				}
			} // End character updates
		}
		else if( respawning )
		{
			if( checkTimer( "respawn" ) > 2.f )
			{
				removeTimer( "respawn" );
				startGame( );
			}
		}
		break;
// Victory
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
