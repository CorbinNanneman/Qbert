#pragma once

#include "GameObject.h"
#include <vector>

class Overlay
{
public:
	Overlay( );

	//void ptr later
	void createObjects( float scale, __int16 screenWidth, __int8 gState, void const **sArgs );
	void update( float timerIncVal, __int8 gState, const void **sArgs );
	void clearObjects( );

	std::vector< GameObject * > &getElements( );

	~Overlay( );

private:
	void addElement( float scale, const char* texPath, __int16 texWidth, __int16 texHeight, 
		__int16 x, __int16 y, __int8 tAFrames = 0, float aDelay = 0.f );

	std::vector< GameObject * > elements;
	bool vanished;
};
