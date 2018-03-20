#include "overlay.h"

Overlay::Overlay( )
{ 
	vanished = true;
}


Overlay::~Overlay( )
{ }


std::vector< GameObject * > &Overlay::getElements( )
{
	std::vector< GameObject * > *retVec;
	if( !vanished )
		retVec ;
	else
		;
	return *retVec;
}


void Overlay::clearObjects( )
{
	while( elements.size( ) > 0 )
	{
		delete elements.at( 0 );
		elements.erase( elements.begin );
	}
}


void Overlay::vanish( )
{
	vanished = true;
}


void Overlay::unvanish( )
{
	vanished = false;
}
