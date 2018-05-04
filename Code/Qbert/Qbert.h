#pragma once

#include "Character.h"

class Qbert : public Character
{
public:
	Qbert( float scale, __int16 screenWidth );

	__int8 update( float fpsScale, __int16 screenWidth, float scale, bool diskbound,
		float fps );
	void move( __int8 direction, float scale );
	void moveAnimate( __int8 state ) override;

	float getTX( );
	float getTY( );
	float getLX( );
	float getLY( );
	__int8 getLRow( );
	__int8 getLIndex( );

	bool Qbert::isSpinning( );
	__int8 Qbert::getDiskIndex( );
	void Qbert::setSpin( bool isSpin );
	void Qbert::setDiskIndex( __int8 newDIndex );

	~Qbert( );
private:
	float targetX, lastX, targetY, lastY;
	__int8 lastRow, lastIndex;
	bool spinning;
	float spinTimer;
	__int8 diskIndex;
};
