#include "statemanager.h"

StateManager::StateManager( )
{
	// FPS Tracking
	targetFps = 60;
	frame = 0;
	fps = targetFps;
	fpsScale = targetFps * 1.0 / fps;

	// Window
	screenWidth = 800;
	screenHeight = screenWidth;
	scale = 3;
	window.create( sf::VideoMode( screenWidth, screenHeight ), "Q*Bert" );
	window.setFramerateLimit( 120 );

	// Platform initialization
	q = new Qbert( scale, screenWidth );
	char* texStrings[ 3 ] = { "./images/blueBlue.png", "./images/blueBlack.png", "./images/blueTiedye1.png" };
	platform.createMap( texStrings, screenWidth, scale );

	state = game;
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
		fpsScale = targetFps * 1.0 / fps;
		frame = 0;
		fpsTimer.restart( );
	}

	// Events
	sf::Event e;
	while( window.pollEvent( e ) )
	{
		if( e.type == sf::Event::Closed )
			window.close( );
		else if( e.key.code == sf::Keyboard::Escape )
			window.close( );
		else if( e.key.code == sf::Keyboard::D )
			q->move( 0, scale, fpsScale );
		else if( e.key.code == sf::Keyboard::C )
			q->move( 1, scale, fpsScale );
		else if( e.key.code == sf::Keyboard::Z )
			q->move( 2, scale, fpsScale );
		else if( e.key.code == sf::Keyboard::S )
			q->move( 3, scale, fpsScale );
	}

	// Spawns
	if( spawnTimer.getElapsedTime( ).asMilliseconds( ) > 1560 )
	{
		characters.push_back( new RedBall( scale, screenWidth, 0.75 ) );
		spawnTimer.restart( );
	}

	// Updates
	// Q*Bert update
	__int8 qReturn = q->update( fpsScale, screenWidth, scale, frame );
	switch( qReturn )
	{
	default:
	case 0:
		break;
	case 1: // Q*Bert completed jump
		platform.changeCube( q->getRow( ), q->getIndex( ), 0, 1 );
		break;
	case 2: // Q*Bert fell off world
		q->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
		break;
	}
	// Characters updates
	for( int i = 0; i < characters.size( ); i++ )
	{
		__int8 charReturn = characters.at( i )->update( fpsScale, screenWidth, scale, frame );
		switch( charReturn )
		{
		default:
		case 0:
		case 1:
			break;
		case 2: // Character Fell off world
			characters.at( i )->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
			break;
		}
	}
}


void StateManager::display( )
{
	// Draw characters behind map when OOB
	if( q->isOOB( ) )
		window.draw( *q->getSprite( ) );
	for( int i = 0; i < characters.size( ); i++ )
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
