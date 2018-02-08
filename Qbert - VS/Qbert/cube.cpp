#include "cube.h"

Cube::Cube()
{
	colorState = 0;
	texRectWidth = 32;
	texRectHeight = 32;
}


Cube::~Cube()
{
}


void Cube::setState(uint8_t newState)
{
	colorState = newState;
}


uint8_t Cube::getState()
{
	return colorState;
}
