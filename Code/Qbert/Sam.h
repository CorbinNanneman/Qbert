#pragma once

#include "Character.h"

class Sam : public Character
{
public:
	Sam(float scale, __int16 screenWidth, float jumpCD);

	__int8 update(float fpsScale, __int16 screenWidth, float scale) override;
	void moveAnimate(__int8 state) override;

	~Sam();

private:

};