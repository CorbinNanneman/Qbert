#pragma once
/*
Date Created:
	Feburary 1st, 2018
Date Last Modified:
	Feburary 1st, 2018 | 12:03PM
*/

#include "gameObject.h"

class Cube : public GameObject
{
public:
	Cube();

	void setState(uint8_t newState);
	uint8_t getState();

	~Cube();
private:
	uint8_t colorState;
};
