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
#include <vector>

class Overlay
{
public:
	Overlay( );

	std::vector< GameObject * > &getElements( );

	void createObjects( );
	void clearObjects( );

	void vanish( );
	void unvanish( );

	~Overlay( );

private:
	std::vector< GameObject * > elements;
	bool vanished;
};
