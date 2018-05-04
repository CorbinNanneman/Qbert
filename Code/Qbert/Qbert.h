#pragma once

#include "Character.h"

class Qbert : public Character
{
public:
	Qbert( float scale, __int16 screenWidth );

	__int8 update(float fpsScale, __int16 screenWidth, float scale, bool diskbound, float fps);
	void move( __int8 direction, float scale, float fpsScale );
	void moveAnimate( __int8 state ) override;
	
	float getTX( );
	float getTY( );
	float getLX( );
	float getLY( );
	
	bool isSpinning();
	__int8 getDiskIndex();
	void setDiskIndex(__int8 newDIndex);
	void setSpin(bool);
	

	~Qbert( );
private:
	float targetX, lastX, targetY, lastY;
	__int8 diskIndex;

	bool spinning;
	float spinTimer;
};
