#pragma once

#include "GameObject.h"

class Character : public GameObject
{
public:
	Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth, 
		float jumpCD );

	virtual __int8 update( float fpsScale, __int16 screenWidth, float scale );
	virtual void move( __int8 direction, float scale );

	virtual void moveAnimate( __int8 state ) = 0;

	void setRow( __int8 newRow, float scale, __int16 screenWidth );
	void setIndex( __int8 newIndex, float scale, __int16 screenWidth );

	__int8 getRow( );
	__int8 getIndex( );
	__int8 getID( );

	bool isOOB( );
	bool isJumping( );

	~Character();

protected:
	__int8 jumpState,
		   id;
	float jumpTimer, jumpCDTime;
	
private:
	__int8 row, 
		   index;
	bool OOB;
};
