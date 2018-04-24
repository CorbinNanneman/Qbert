#include "Disk.h"
#include <time.h>

Disk::Disk(float scale) : GameObject(scale, 4, .2)
{
	setTexture("./images/diskBlue.png", 16, 10);
}


__int8 Disk::getRow()
{
	return row;
}


__int8 Disk::getIndex()
{
	return index;
}

void Disk::randomizePos()
{
	row = rand() % 7 - 1;

	if (rand() % 2 == 0)
		index = -1;
	else
		index = row + 1;
}


Disk::~Disk()
{
}
