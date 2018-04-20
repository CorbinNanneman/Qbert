#pragma once

#include "Character.h"

class Slick : public Character
{
public:
	Slick(float scale, __int16 screenWidth, float jumpCD, float movementScale);

	__int8 update(float fpsScale, __int16 screenWidth, float scale) override;
	void moveAnimate(__int8 state) override;

	~Slick();

private:

};