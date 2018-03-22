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
| Authors: Greg Francis                                          |
|                                                                |
| Date Last Updated: March 20th, 2018 | 10:55am                  |
|                                                                |
\*==============================================================*/

#include "gameobject.h"
#include <vector>

class Overlay
{
public:
	Overlay( );

	void createObjects( __int8 lives, __int32 score, __int8 round, __int8 level, 
		float scale );
	void update( __int32 score );
	void clearObjects( );

	std::vector< GameObject * > &getElements( );

	~Overlay( );

private:
	std::vector< GameObject * > elements;
	bool vanished;
};
