#pragma once
/*
Represents a character that moves between blocks.

Date Created:
	February 8th, 2018
Date Last Modified:
	February 8th, 2018 | 12:00 PM
*/

#include "gameObject.h"

class Character : public GameObject
{
public:
	Character();

	void moveUR();
	void moveDR();
	void moveDL();
	void moveUL();

	~Character();
private:
	uint8_t row, index;
};
