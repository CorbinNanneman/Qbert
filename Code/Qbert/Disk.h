#pragma once

#include "GameObject.h"

class Disk : public GameObject
{
public:
	Disk(float scale);

	__int8 getRow();
	__int8 getIndex();
	void randomizePos();

	~Disk();

private:
	__int8 row, index;
};
