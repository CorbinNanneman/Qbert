#pragma once
/*
Represents a character that moves between blocks.

Date Created:
	February 8th, 2018
Date Last Modified:
	February 8th, 2018 | 12:00 PM
*/

#include "gameObject.h"

class Character : public GameObject
{
public:
	Character( uint8_t startRow, uint8_t startIndex, int scale, double screenWidth );

	void update( int frame ) override;
	void moveUR();
	void moveDR();
	void moveDL();
	void moveUL();
	bool moveOOB( uint8_t row, uint8_t index );

	~Character();
private:
	uint8_t row, 
			index;
	unsigned int jumpTimer;
	bool isOOB;
};
