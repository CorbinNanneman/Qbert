#pragma once

#include "Character.h"

class Ugg : public Character
{
public:
	Ugg(float scale, __int16 screenWidth, float jumpCD);

	__int8 update(float fpsScale, __int16 screenWidth, float scale) override;
	void moveAnimate(__int8 state) override;

	~Ugg();
};

