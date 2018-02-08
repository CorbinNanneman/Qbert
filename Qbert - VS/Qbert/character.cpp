#include "character.h"

Character::Character()
{
}


Character::~Character()
{
}


void Character::moveUR()
{
	// Up Right Bounds Check
	if (row < 0 || index < row + 1)
		row--;

	// setVX();
}


void Character::moveDR()
{

}


void Character::moveDL()
{

}


void Character::moveUL()
{

}
