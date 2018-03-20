#pragma once
/*==============================================================*\
|                                                                |
| Program: Qbert                                                 |
|                                                                |
| Breif: Classic arcade game recreated in C++                    |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| Class: Character                                               |
|                                                                |
| Purpose: Provide basic functions for the game's characters     |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| Authors: Greg Francis, Ben Ewing                               |
|                                                                |
| Date Last Updated: March 20th, 2018 | 10:55am                  |
|                                                                |
\*==============================================================*/

#include "gameobject.h"

class Character : public GameObject
{
public:
	Character( __int8 startRow, __int8 startIndex, float scale, __int16 screenWidth, 
		float jumpCD );

	virtual __int8 update( float fpsScale, __int16 screenWidth, float scale, __int16 frame );
	void move( __int8 direction, float scale, float fpsScale );

	virtual void moveAnimate( __int8 state ) = 0;

	__int8 getRow( );
	__int8 getIndex( );
	__int8 getJumpState( );
	bool isOOB( );
	bool isJumping( );

	~Character();

protected:
	__int8 jumpState;
	float jumpTimer, jumpCDTime;
	
private:
	__int8 row, 
		   index;
	bool OOB;
};
