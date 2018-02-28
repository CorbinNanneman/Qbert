#pragma once

#include "character.h"

class RedBall : public Character
{
public:
	RedBall( float scale, __int16 screenWidth, float jumpCD );

	void update( float fpsScale, __int16 screenWidth, float scale, __int16 frame ) override;
	void moveAnimate( __int8 state ) override;

	~RedBall( );

private:

};