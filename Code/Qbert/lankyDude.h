#pragma once
#include "character.h"
class LankyDude:
	public Character
{
public:
	LankyDude(float scale, __int16 screenWidth, float jumpCD);

	__int8 update(float fpsScale, __int16 screenWidth, float scale, __int16 frame) override;
	void moveAnimate(__int8 state) override;

	~LankyDude();
};
