#include "Overlay.h"

Overlay::Overlay( )
{ }


Overlay::~Overlay( )
{ }


void Overlay::createObjects( float scale, __int16 screenWidth, __int8 gState, void const **sArgs )
{
	// __int8 player, __int8 lives, __int32 score, __int8 round, __int8 level, const char* targetTexStr
	// Player
	switch( gState )
	{
	case 3: // Game
		/** sArgs
		 0 = __int8 player
		 1 = __int8 lives
		 2 = __int32 score
		 3 = __int8 round
		 4 = __int8 level
		 5 = const char *targetTexStr
		*/
		if( *static_cast< const __int8 * >( sArgs[ 0 ] ) == 1 )
			addElement( scale, "./images/player1.png", 51, 7, 
				screenWidth / 2 - static_cast< __int16 >( 87 * scale), static_cast< __int16 >( 10 * scale ),
				6, 0.08f );
		else
			addElement( scale, "./images/player2.png", 51, 7, 
				screenWidth / 2 - static_cast< __int16 >( 87 * scale ), static_cast< __int16 >( 10 * scale ),
				6, 0.08f );
		// Player #
		addElement( scale, "./images/playerNum.png", 8, 11, 
			screenWidth / 2 - static_cast< __int16 >( 52 * scale ), static_cast< __int16 >( 10 * scale ) );
		elements.at( 1 )->setTexRect( *static_cast< const __int8 * >( sArgs[ 0 ] ) - 1, 0 );
		// Score
		elements.push_back( new GameObject( ) );
		// Change To:
		addElement( scale, "./images/changeTo.png", 47, 5, 
			screenWidth / 2 - static_cast< __int16 >( 89 * scale ), static_cast< __int16 >( 37 * scale ) );
		// Target Arrows
		addElement( scale, "./images/arrows.png", 48, 7, 
			screenWidth / 2 - static_cast< __int16 >( 88 * scale ), static_cast< __int16 >( 49 * scale ),
			3, 0.6f );
		// Target Cube
		addElement( scale, static_cast< const char * >( sArgs[ 5 ] ), 14, 12, 
			screenWidth / 2 - static_cast< __int16 >( 88 * scale ), static_cast< __int16 >( 49 * scale ) );
		// Lives Counter
		elements.push_back( new GameObject( ) );
		// Level:
		addElement( scale, "./images/level.png", 28, 5,
			screenWidth / 2 + static_cast< __int16 >( 88 * scale ), static_cast< __int16 >( 37 * scale ) );
		// Level Num
		addElement( scale, "./images/numGreen.png", 6, 6,
			screenWidth / 2 + static_cast< __int16 >( 110 * scale ), static_cast< __int16 >( 37 * scale ) );
		elements.at( 8 )->setTexRect( *static_cast< const __int8 * >( sArgs[ 4 ] ), 0 );
		// Round:
		addElement( scale, "./images/round.png", 30, 5,
			screenWidth / 2 + static_cast< __int16 >( 88 * scale ), static_cast< __int16 >( 47 * scale ) );
		// Round Num
		addElement( scale, "./images/numOrange.png", 6, 6,
			screenWidth / 2 + static_cast< __int16 >( 110 * scale ), static_cast< __int16 >( 47 * scale ) );
		elements.at( 10 )->setTexRect( *static_cast< const __int8 * >( sArgs[ 4 ] ), 0 );
		break;
	}
}


/* Element Position In Vector
 0 - Player
 1 - Player Number
 2 - Score
 3 - Change To:
 4 - Target Arrows
 5 - Target Cube
 6 - Lives Counter
 7 - Level:
 8 - Level Num
 9 - Round:
 10 - Round Num
*/

void Overlay::update( float timerIncVal, __int8 gState, void const **sArgs )
{
	switch( gState )
	{
	case 3:
		elements.at( 0 )->update( timerIncVal );
		elements.at( 4 )->update( timerIncVal );
		break;
	default:
		break;
	}
}


void Overlay::clearObjects( )
{
	while( elements.size( ) > 0 )
	{
		delete elements.at( 0 );
		elements.erase( elements.begin( ) );
	}
}


std::vector< GameObject * > &Overlay::getElements( )
{
	return elements;
}


void Overlay::addElement( float scale, const char *texPath, __int16 texWidth, 
	__int16 texHeight, __int16 x, __int16 y, __int8 tAFrames, float aDelay )
{
	GameObject *g = new GameObject( scale, tAFrames, aDelay );
	g->setTexture( texPath, texWidth, texHeight );
	g->setX( x );
	g->setY( y );
	elements.push_back( g );
}
