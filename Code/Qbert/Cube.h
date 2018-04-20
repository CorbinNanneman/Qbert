#pragma once

#include "GameObject.h"

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
