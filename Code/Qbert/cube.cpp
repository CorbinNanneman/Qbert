#include "cube.h"

Cube::Cube()
{
	colorState = 0;
}


Cube::~Cube()
{ }


void Cube::setState(__int8 newState)
{
	colorState = newState;
}


__int8 Cube::getState()
{
	return colorState;
}
