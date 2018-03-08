#include "statemanager.h"
#include "redball.h"

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

	startGame( );
}


void StateManager::startGame( )
{
	// Objects
	q = new Qbert( scale, screenWidth );
	char* texStrings[ 3 ] = { "./images/blueBlue.png", "./images/blueTiedye1.png", 
		"./images/blueBlack.png" };
	platform.createMap( texStrings, screenWidth, scale );

	// Data
	state = game;
	paused = false;
	pauseKeyHeld = false;
}


// Reset all data to initial states
void StateManager::clear( )
{
	// Objects
	delete q;
	while( characters.size( ) != 0 )
		destroyCharacter( characters.at( 0 ) );
	platform.deleteMap( );

	// Timers

}


StateManager::~StateManager( )
{ 
	delete q;
	platform.deleteMap( );
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
	if( fpsTimer.getElapsedTime( ).asMilliseconds( ) > 999 )
	{
		fps = frame;
		// Determines adjustment needed to match proper frame rate
		fpsScale = targetFps * 1.f / fps;
		frame = 0;
		fpsTimer.restart( );
	}

// System Events
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
				q->move( 0, scale, fpsScale );
				break;
			case sf::Keyboard::C:
				q->move( 1, scale, fpsScale );
				break;
			case sf::Keyboard::Z:
				q->move( 2, scale, fpsScale );
				break;
			case sf::Keyboard::S:
				q->move( 3, scale, fpsScale );
				break;
			case sf::Keyboard::P:
				if( !pauseKeyHeld )
					paused = !paused;
				pauseKeyHeld = true;
				break;
			default:
				break;
			} // end switch - Keyboard Input
			break;
		} // end switch - Event Type
	} // end loop - Event Checking

	// Update status of pause key when no longer held
	if( pauseKeyHeld )
		if( !sf::Keyboard::isKeyPressed( sf::Keyboard::P ) )
			pauseKeyHeld = false;


	if( !paused )
	{
// Spawns
	if( spawnTimer.getElapsedTime( ).asMilliseconds( ) > 1560 )
	{
		characters.push_back( new RedBall( scale, screenWidth, 1.25 ) );
		spawnTimer.restart( );
	}

// Updates
	switch( state )
	{
	case game:
	// Q*Bert update
		__int8 qReturn = q->update( fpsScale, screenWidth, scale, frame );
		switch( qReturn )
		{
		default:
		case 0:
			break;
		case 1: // Q*Bert is jumping
			// Check for collision
			for( int i = 0; i < characters.size( ); i++ )
			{
				if( checkCollision( q, characters.at( i ) ) )
				{
					destroyCharacter( characters.at( i ) );
					// DIE QBERT DIE
				}
			} // end loop - character collision checking
			break;
		case 2: // Q*Bert completed jump
			platform.changeCube( q->getRow( ), q->getIndex( ), 0, 1 );
		
			if( platform.isComplete( ) )
			{
				platform.deleteMap( );
				char* texStrings[ 3 ] = { "./images/blueBlue.png", "./images/blueTiedye1.png", 
					"./images/blueBlack.png" };
				platform.createMap( texStrings, screenWidth, scale );
			} // end if - Platform Completed
			break;
		case 3: // Q*Bert fell off world
			q->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
			break;
		} // end switch - qbert return

	// Characters updates
		for( unsigned __int8 i = 0; i < characters.size( ); i++ )
		{
			__int8 charReturn = characters.at( i )->update( fpsScale, screenWidth, scale, frame );
			switch( charReturn )
			{
			default:
			case 0:
			case 1: // Character is jumping
				if( checkCollision( characters.at( i ), q ) )
				{
					destroyCharacter( characters.at( i ) );
					// DIE QBERT DIE
				}
				break;
			case 2: // Character completes jump
				break;
			case 3: // Character fell off world
				destroyCharacter( characters.at( i ) );
				break;
			} // endswitch - character return
		} // endfor - character vector loop
		break;
	default:
		break;
	} // end switch - game state
	} // endif - !paused
}


void StateManager::display( )
{
	// Draw characters behind map when OOB
	if( q->isOOB( ) )
		window.draw( *q->getSprite( ) );
	for( unsigned __int8 i = 0; i < characters.size( ); i++ )
		if( characters.at( i )->isOOB( ) )
			window.draw( *characters.at( i )->getSprite( ) );

	// MAP DRAW
	Cube** map = platform.getCubes( );
	for( int row = 0; row < 7; row++ )
	{
		for( int index = 0; index < row + 1; index++ )
			window.draw( *map[ row ][ index ].getSprite( ) );
	}

	// Draw characters in front of map when in bounds
	if( !q->isOOB( ) )
		window.draw( *q->getSprite( ) );
	for( unsigned int i = 0; i < characters.size( ); i++ )
		if( !characters.at( i )->isOOB( ) )
			window.draw( *characters.at( i )->getSprite( ) );

	window.display( );
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


bool StateManager::checkCollision( Character *c1, Character *c2 )
{
	// Calculated Distance
	int xDist = c1->getX( ) - c2->getX( ),
		yDist = c1->getY( ) - c2->getY( ),
		boundsFactor = 8 * scale;

	return xDist > -boundsFactor && xDist < boundsFactor && yDist > -boundsFactor && yDist < boundsFactor;
}
