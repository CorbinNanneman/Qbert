#pragma once

#include "character.h"

class Qbert : public Character
{
public:
	Qbert( float scale, __int16 screenWidth );

	void moveAnimate( __int8 state ) override;

	~Qbert( );
};