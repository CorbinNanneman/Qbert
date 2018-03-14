#include "monkey.h"
#include "time.h"
#include <iostream>

Monkey::Monkey(float scale, __int16 screenWidth,
	float jumpCD) : Character(7,7,scale,screenWidth,jumpCD)
{
	setTexture("./images/monkey.png", 16, 16);
	
}

void Monkey::move(__int8 direction, float scale, float fpsScale)
{
	if (jumpTimer > jumpCDTime && !OOB)
	{
		moveAnimate(direction);
		switch (direction) //Only conditions are down left and down right, or up left and straight right depending on view
		{
		case 3:
			setVX(56 * scale / ((60 / fpsScale) / 2));
			setVY(-22 * scale / ((60 / fpsScale) / 2));
			break;
		case 4: //Left
			setVX(40 * scale / ((60 / fpsScale) / 2));
			setVY(2 * scale / ((60 / fpsScale) / 2));
			break;
		}
		jumpTimer = 0;
		jumpDirection = direction;
	}
}

__int8 Monkey::update(float fpsScale, __int16 screenWidth, float scale, __int16 frame)
{
	GameObject::update();
	__int8 retVal = 0;
	jumpTimer += 1 / (60 / fpsScale);

	// Character is jumping
	if (jumpDirection < 6)
	{
		// Character continues jumping
		if (jumpTimer < 0.5 || OOB)
		{
			if (OOB && isOffScreen(screenWidth, screenWidth, scale))
				retVal = 3;
			else
				retVal = 1;
			setVX(getVX() - 9.8 * fpsScale * scale / (60 / fpsScale));
		}
		// Character completes jump
		else
		{
			// Adjust character position
			switch (jumpDirection)//Only conditions are down left and down right, or up left and straight right depending on view
			{
			case 3: // Up left
				row--;
				index--;
				break;
			case 4: //Left
				index--;
				break;
			}
			if (index == 0)
				OOB = true;
			else
			{
				moveAnimate(jumpDirection + 4);
				// Ensure Exact Position
				setVX(0);
				setVY(0);
				setX(32 * scale * (row * -.5 + index) + screenWidth / 2);
				setY(scale * (row * 24 - 16) + 100);
				jumpDirection = 6; // Stopped moving
				retVal = 2;
			}
		} 
	}
	if (OOB)
	{
		//setVY(getVY() - 9.8 * fpsScale * scale / (60 / fpsScale));
		setVX(getVX() - 9.8 * fpsScale * scale / (60 / fpsScale));
	}
	if (jumpTimer > jumpCDTime)
			move(rand() % 2 + 3, scale, fpsScale);

	return retVal;
}

void Monkey::moveAnimate(__int8 state)
{
	switch (state) 
	{
	case 3: //Resting left
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 4: //Resting right
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth *5, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 7: //Jumping left
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	case 8: //Jumping right
		getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth*4, 0),
			sf::Vector2i(texWidth, texHeight)));
		break;
	}
}

Monkey::~Monkey()
{
}
