#pragma once

#include "character.h"

class Snake : public Character
{
public:
	Snake(float scale, __int16 screenWidth, float jumpCD);

	__int8 update(float fpsScale, __int16 screenWidth, float scale) override;
	void moveAnimate(__int8 state) override;
	void setTarget(__int16 tX, __int16 tY);
	~Snake();

private:
	__int16 targetX;
	__int16 targetY;
	bool isEgg;
};