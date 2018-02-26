#pragma once

#include "character.h"

class RedBall : public Character
{
public:
	RedBall( float scale, __int16 screenWidth );

	void moveAnimate( __int8 state ) override;

	~RedBall( );
};