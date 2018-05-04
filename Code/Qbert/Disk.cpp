#include "Disk.h"
#include <time.h>

Disk::Disk(float scale) : GameObject(scale, 4, .2)
{
	setTexture("./images/diskBlue.png", 16, 10);
	setYOffset(-8.f * scale);
}


Disk::~Disk( )
{ }


void Disk::randomizePos( )
{
	row = rand( ) % 7 - 1;

	if( rand( ) % 2 == 0 )
		index = -1;
	else
		index = row + 1;
}


__int8 Disk::getRow()
{
	return row;
}


__int8 Disk::getIndex()
{
	return index;
}
