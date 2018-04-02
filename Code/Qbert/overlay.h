#pragma once

#include "gameobject.h"
#include <vector>

class Overlay
{
public:
	Overlay( );

	void createObjects( __int8 player, __int8 lives, __int32 score, __int8 round, __int8 level, 
		float scale );
	void update( __int32 score );
	void clearObjects( );

	std::vector< GameObject * > &getElements( );

	~Overlay( );

private:
	void addElement( float scale, const char* texPath, __int16 texWidth, __int16 texHeight, 
		__int16 x, __int16 y );

	std::vector< GameObject * > elements;
	bool vanished;
};
