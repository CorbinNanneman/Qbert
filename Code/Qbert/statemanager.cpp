#include "statemanager.h"
#include "redball.h"

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

	// Platform initialization
	q = new Qbert( scale, screenWidth );
	char* texStrings[ 3 ] = { "./images/blueBlue.png", "./images/blueTiedye1.png", "./images/blueBlack.png" };
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


// For use in update
bool checkCollision( Character *c1, Character *c2 )
{
	int rowDist = c1->getRow( ) - c2->getRow( ),
		indexDist = c1->getIndex( ) - c2->getIndex( );
	// True if index and row are close enough to each other
	return rowDist > -0.3f && rowDist < 0.3f && indexDist > -0.3f && indexDist < 0.3f;
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
		characters.push_back( new RedBall( scale, screenWidth, 1.25 ) );
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
	case 1: // Q*Bert is jumping
		// Find nearby characters to check positions
		for( int i = 0; i < characters.size( ); i++ )
		{
			if( checkCollision( q, characters.at( i ) ) )
			{
				characters.at( i )->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
				q->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
			}
		}
		break;
	case 2: // Q*Bert completed jump
		platform.changeCube( q->getRow( ), q->getIndex( ), 0, 1 );
		if( platform.isComplete( ) )
		{
			platform.deleteMap( );
			char* texStrings[ 3 ] = { "./images/blueBlue.png", "./images/blueTiedye1.png", 
				"./images/blueBlack.png" };
			platform.createMap( texStrings, screenWidth, scale );
		}
		break;
	case 3: // Q*Bert fell off world
		q->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
		break;
	}
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
				characters.at( i )->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
				q->getSprite( )->setTextureRect( sf::IntRect( 0, 0, 0, 0 ) );
			}
			break;
		case 2: // Character completes jump
			break;
		case 3: // Character fell off world
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
