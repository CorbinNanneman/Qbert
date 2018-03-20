#pragma once

#include "character.h"

class Snake : public Character
{
public:
	Snake(float scale, __int16 screenWidth, float jumpCD);

	__int8 update(float fpsScale, __int16 screenWidth, float scale, __int16 frame) override;
	void moveAnimate(__int8 state) override;
	void findTarget(__int8 newTargetRow, __int16 newTarget);
	~Snake();

private:
	__int16 qbertX;
	__int8 qbertRow;
	bool isEgg;
};