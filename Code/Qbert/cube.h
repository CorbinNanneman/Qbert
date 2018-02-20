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

	void setState( __int8 newState );
	__int8 getState();

	~Cube();
private:
	__int8 colorState;
};
