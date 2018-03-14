#pragma once
#include "character.h"
class Monkey :
	public Character
{
public:
	Monkey(float scale, __int16 screenWidth, float jumpCD);

	__int8 update(float fpsScale, __int16 screenWidth, float scale, __int16 frame) override;
	void moveAnimate(__int8 state) override;
	void move(__int8 direction, float scale, float fpsScale);

	~Monkey();
};

