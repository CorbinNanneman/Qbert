#pragma once

#include "character.h"

class Qbert : public Character
{
public:
	Qbert( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth );

	void moveAnimate( __int8 state ) override;

	~Qbert( );
};