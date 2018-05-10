#pragma once

#include "Character.h"

class Qbert : public Character
{
public:
	Qbert( float scale, __int16 screenWidth );

	void move( __int8 direction, float scale );
	void moveAnimate( __int8 state ) override;

	float getTX( );
	float getTY( );
	float getLX( );
	float getLY( );
	__int8 getLRow( );
	__int8 getLIndex( );

	~Qbert( );
private:
	float targetX, lastX, targetY, lastY;
	__int8 lastRow, lastIndex;
};
