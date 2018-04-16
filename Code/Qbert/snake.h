#pragma once

#include "character.h"
#include "qbert.h"

class Snake : public Character
{
public:
	Snake(float scale, __int16 screenWidth, float jumpCD, Qbert *q );

	__int8 update(float fpsScale, __int16 screenWidth, float scale) override;
	void moveAnimate(__int8 state) override;
	void findTarget( );
	~Snake();

private:
	float targetX, targetY;
	bool isEgg;
	Qbert *qbert = nullptr;
};