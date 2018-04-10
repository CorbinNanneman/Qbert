#pragma once

#include "character.h"

class Qbert : public Character
{
public:
	Qbert( float scale, __int16 screenWidth );

	void move( __int8 direction, float scale, float fpsScale ) override;
	void moveAnimate( __int8 state ) override;

	__int16 getTX( );
	__int8 getTRow( );
	__int16 getLX( );
	__int8 getLRow( );

	~Qbert( );
private:
	__int16 targetX, lastX;
	__int8 targetRow, lastRow;
};