#include "overlay.h"

Overlay::Overlay( )
{ }


Overlay::~Overlay( )
{ }


void Overlay::createObjects( __int8 lives, __int32 score, __int8 round, __int8 level, 
	float scale )
{
	GameObject *g = new GameObject( scale );
	g->setTexture( "./images/player1.png", 51, 7 );
	g->setX( 45 );
	g->setY( 24 );
	elements.push_back( g );
}


void Overlay::update( __int32 score )
{

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
