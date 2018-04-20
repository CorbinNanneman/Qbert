#include "StateManager.h"
#include "RedBall.h"
#include "Ugg.h"
#include "Snake.h"
#include "Wrongway.h"
#include "Slick.h"
#include "Sam.h"
#include "MagicBall.h"

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

	timers.addTimer( "windowLoaded", false );
}


StateManager::~StateManager( )
{
	platform.deleteMap( );
	while( characters.size( ) > 0 )
		destroyCharacter( characters.at( 0 ) );
	timers.erase( );
}


void StateManager::startGame( )
{
	// Deallocate any old memory
	if( platform.getCubes( ) != nullptr )
		platform.deleteMap( );
	while( characters.size( ) > 0 )
		destroyCharacter( characters.at( 0 ) );
	timers.erase( );
	overlay.clearObjects( );

	// Create Map
	q = dynamic_cast< Qbert* >( createCharacter( 0 ) );
	const char *texStrings[ 3 ] = { "./images/blueBlue.png", "./images/bluePink.png", 
		"./images/blueYellow.png" };
	platform.createMap( texStrings, screenWidth, scale );

	// Create Overlay
	void const *args[ 6 ];
	const __int8 player = 1, lives = 3, round = 1, level = 1;
	const __int32 score = 0;
	const char *targetTexStr = "./images/blueYellowTarget.png";

	args[ 0 ] = &player;
	args[ 1 ] = &lives;
	args[ 2 ] = &score;
	args[ 3 ] = &round;
	args[ 4 ] = &level;
	args[ 5 ] = targetTexStr;
	overlay.createObjects( scale, screenWidth, game, args );

	// Data
	state = game;

	timers.addTimer( "snakeSpawn", true );
	
	respawning = false;
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
	timers.erase( );

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
		fpsScale = static_cast< float >( targetFps ) / fps;
		frame = 0;
		fpsClock.restart( );
	}
	timers.updateTimers( 1.f / fps, paused );

	//overlay.update( 0, 1.f / fps );

	if( windowLoaded )
	{
		checkEvents( );
		stateUpdate( );
	}
	// This is done to stabilize framerate after window is created.
	else if( timers.checkTimer( "windowLoaded" ) > 5.f )
	{
		windowLoaded = true;
		timers.removeTimer( "windowLoaded" );
		startGame( );
	}
}


void StateManager::display( )
{
	if( windowLoaded )
	{
		std::vector< Character * > frontChars;

		// Draw characters that are behind map
		for( unsigned __int8 i = 0; i < characters.size( ); i++ )
		{
			if( characters.at( i )->getZ( ) < 0 )
				window.draw( *characters.at( i )->getSpritePtr( ) );
			else
				frontChars.push_back( characters.at( i ) );
		}

		// Draw map
		Cube** map = platform.getCubes( );
		for( int row = 0; row < 7; row++ )
		{
			for( int index = 0; index < row + 1; index++ )
				window.draw( *map[ row ][ index ].getSpritePtr( ) );
		}

		// Sort frontChars by zIndex
		if( characters.size( ) > 1 )
		{
			size_t fCSize = frontChars.size( );
			unsigned __int8 i, lockedEls = 0;
			while( fCSize - lockedEls > 1 )
			{
				__int8 lastElI = fCSize - lockedEls - 1;
				i = 0;
				while( i < lastElI )
				{
					// Check if current elment Z is greater than last element Z, 
					// if Z's are equal check if current element Y is greater than last element Y
					if( frontChars.at( i )->getZ( ) > frontChars.at( lastElI )->getZ( ) || 
						( frontChars.at( i )->getZ( ) == frontChars.at( lastElI )->getZ( ) &&
							frontChars.at( i )->getY( ) > frontChars.at( lastElI )->getY( ) ) )
					{
						// Swap Elements
						Character *swap = frontChars.at( i );
						frontChars.at( i ) = frontChars.at( lastElI );
						frontChars.at( lastElI ) = swap;
					}
					i++;
				}
				lockedEls++;
			}
		}

		// Draw characters that are in front of map
		for( unsigned __int8 i = 0; i < frontChars.size( ); i++ )
			window.draw( *frontChars.at( i )->getSpritePtr( ) );

		// Draw overlay
		std::vector< GameObject * > &elements = overlay.getElements( );
		for( unsigned int i = 0; i < elements.size( ); i++ )
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
				if( !pauseKeyHeld && !respawning )
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
 2 - Ugg (RtL Monkey)
 3 - Wrongway (LtR Monkey)
 4 - Red Ball
 5 - Magic Ball
 6 - Slick
 7 - Sam
*/
void StateManager::stateUpdate( )
{
	overlay.update( 1.f / fps, game, NULL );
	switch( state )
	{
// Game
	case game:
		if( !paused )
		{
	// Spawns
			if( timers.checkTimer( "snakeSpawn" ) > 4.0f )
			{
				createCharacter( 1 );
				timers.removeTimer( "snakeSpawn" );
				timers.addTimer( "spawn", true );
			}
			if( timers.checkTimer( "spawn" ) > 4.3f )
			{
				createCharacter( 5 );
				timers.resetTimer( "spawn" );
			}
	// Character updates
			static __int8 qReturn;
			bool collided;
			for( unsigned __int8 i = 0; i < characters.size( ); i++ )
			{
				// Shortened character handle
				Character *curChar = characters.at( i );
				
				if( curChar != nullptr )
				{
				__int8 charReturn = curChar->update( fpsScale, screenWidth, scale);
				if( curChar == q )
					qReturn = charReturn;

				switch( charReturn )
				{
				default:
				case 0: // Character does nothing
					break;
				case 1: // Character is jumping
					if( !q->isOOB( ) )
					{
						collided = false;
						Character *collidedChar = curChar;
						// Collision check for non-Qbert characters
						if( curChar != q )
						{
							if( checkCollision( q, curChar ) )
								collided = true;
						}
						// Collision check for Qbert
						else
						{
							for( unsigned int i = 0; !collided && i < characters.size( ); i++ )
							{
								if( q != characters.at( i ) && checkCollision( q, characters.at( i ) ) )
								{
									collided = true;
									collidedChar = characters.at( i );
								}
							}
						}

						// Qbert collided w/ enemy
						if( collided )
						{
							if( collidedChar->getID( ) < 5 )
							{
								paused = true;
								respawning = true;
								timers.addTimer( "respawn", false );
							}
							else
								destroyCharacter( collidedChar );
						}
					}
					break;
				case 2: // Character completes jump
					switch( curChar->getID( ) )
					{
					case 0: // Qbert
						platform.changeCube( q->getRow( ), q->getIndex( ), 0, 1 );
						if( platform.isComplete( ) )
							transitionState( victory );
						break;
					case 6: // Slick
						platform.changeCube( curChar->getRow( ), curChar->getIndex( ), 2, 1 );
						break;
					case 7: // Sam
						platform.changeCube( curChar->getRow( ), curChar->getIndex( ), 1, 1 );
					default:
						break;
					}
					break;
				case 3: // Character fell off world
					if( curChar == q )
					{
						respawning = true;
						timers.addTimer( "respawn", false );
					}
					else
						destroyCharacter( curChar );
					break;
				}
			} // End character updates
			}
		} // End !paused

		if( respawning )
		{
			if( timers.checkTimer( "respawn" ) > 2.f )
			{
				timers.removeTimer( "respawn" );
				startGame( );
			}
		}
		break;
// Victory
	case victory:
		// Flash cubes 9 times
		if( timers.checkTimer( "flash" ) > 0.09f )
		{
			for( int row = 0; row < 7; row++ )
				for( int index = 0; index < row + 1; index++ )
					platform.changeCube( row, index, 0, 5 );
			timers.resetTimer( "flash" );

			if( ++flashChange > 14 )
			{
				timers.removeTimer( "flash" );
				startGame( );
			}
		}
		break;

	default:
		break;
	}
}


void StateManager::transitionState( __int8 newState )
{
	switch( newState )
	{
	case game:
		break;
	case victory:
		timers.addTimer( "flash", true );
		flashChange = 0;
		state = victory;
		break;
	default:
		break;
	}
}


bool StateManager::checkCollision( Character *c1, Character *c2 )
{
	bool collision = false;
	
	if( c1 != c2 )
	{
		float xDist = c1->getX( ) - c2->getX( ), 
			yDist = c1->getY( ) - c2->getY( ),
			boundsFactor = 8 * scale;
		if( xDist > -boundsFactor && xDist < boundsFactor && yDist > -boundsFactor && 
			yDist < boundsFactor )
			collision = true;
	}
	return collision;
}


Character* StateManager::createCharacter( __int8 characID )
{
	Character *c = nullptr;
	switch( characID )
	{
	case 0: // Qbert
		c = new Qbert( scale, screenWidth );
		break;
	case 1: // Snake
		c = new Snake( scale, screenWidth, 0.7f, q );
		break;
	case 2: // Ugg (RtL Monkey)
		c = new Ugg( scale, screenWidth, 1.1f );
		break;
	case 3: // Wrongway (LtR Monkey)
		c = new Wrongway( scale, screenWidth, 1.1f );
		break;
	case 4: // Red Ball
		c = new RedBall( scale, screenWidth, 1.1f );
		break;
	case 5: // Magic Ball
		c = new MagicBall( scale, screenWidth, 1.0f );
		break;
	case 6: // Slick
		c = new Slick( scale, screenWidth, 0.75f, scale * fpsScale );
		break;
	case 7: // Sam
		c = new Sam( scale, screenWidth, 0.75f, scale * fpsScale );
		break;
	default:
		break;
	}
	characters.push_back( c );
	return c;
}


void StateManager::destroyCharacter( Character *c )
{
	bool deleted = false;
	for( unsigned int i = 0; !deleted && i < characters.size( ); i++ )
	{
		if( c == characters.at( i ) )
		{
			delete c;
			characters.erase( characters.begin( ) + i );
			deleted = true;
		}
	}
}
