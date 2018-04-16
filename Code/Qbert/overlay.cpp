#include "overlay.h"

Overlay::Overlay( )
{ }


Overlay::~Overlay( )
{ }


void Overlay::createObjects( __int8 player, __int8 lives, __int32 score, __int8 round,
	__int8 level, float scale, __int16 screenWidth )
{
	// Player
	if( player == 1 )
		addElement( scale, "./images/player1.png", 51, 7, screenWidth / 2 - 87 * scale, 10 * scale );
	else
		addElement( scale, "./images/player2.png", 51, 7, screenWidth / 2 - 87 * scale, 10 * scale );
	timers.addTimer( "playerAnim", true );
	// Player #
	addElement( scale, "./images/playerNum.png", 8, 11, screenWidth / 2 - 52 * scale, 10 * scale );
	elements.at( 1 )->setTexRect( player - 1, 0 );
	// Score
	
	// Change To:
	addElement( scale, "./images/changeTo.png", 47, 5, screenWidth / 2 - 89 * scale, 37 * scale );
	// Target Arrows
	addElement( scale, "./images/arrows.png", 48, 7, screenWidth / 2 - 88 * scale, 41 * scale );
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
void Overlay::update( __int32 score, float timerIncVal )
{
	timers.updateTimers( timerIncVal, false );
	
	if( timers.checkTimer( "playerAnim" ) > 0.1f )
	{

		timers.resetTimer( "playerAnim" );
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


void Overlay::addElement( float scale, const char* texPath, __int16 texWidth, 
	__int16 texHeight, __int16 x, __int16 y )
{
	GameObject *g = new GameObject( scale );
	g->setTexture( texPath, texWidth, texHeight );
	g->setX( x );
	g->setY( y );
	elements.push_back( g );
}
