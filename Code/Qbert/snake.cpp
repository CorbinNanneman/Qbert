#include "Snake.h"
#include "time.h"
#include <iostream>

Snake::Snake(float scale, __int16 screenWidth, float jumpCD)
	: Character(1, rand() % 2, scale, screenWidth, jumpCD)
{
	isEgg = true;
	setTexture("./images/snakeEgg.png", 16, 12);
}

__int8 Snake::update(float fpsScale, __int16 screenWidth, float scale, __int16 frame)
{
	__int8 retVal = Character::update(fpsScale, screenWidth, scale, frame);

	if (isEgg)
	{
		if (jumpTimer > jumpCDTime)
			Character::move(rand() % 2 + 1, scale, fpsScale);

		if (getRow() == 6)
		{
			setTexture("./images/snake.png", 16, 32);
			isEgg = false;
		}
	}
	else
	{        //attemting to get a reletive x coordinate 
	
		
		if (qbertRow < getRow())
		{
			if (qbertX == GameObject::getX())
				Character::move(rand() % 2 * 3, scale, fpsScale);

			if (qbertX > GameObject::getX())
				Character::move(0, scale, fpsScale);
			else
				Character::move(3, scale, fpsScale);

			//move up
		}
		else if (qbertRow > getRow())
		{


			if (qbertX == GameObject::getX())
				Character::move(rand() % 2 + 1, scale, fpsScale);

			if (qbertX > GameObject::getX())
				Character::move(1, scale, fpsScale);
			else
				Character::move(2, scale, fpsScale);
			//move down
		}
		else
		{
			if (getRow() == 6)
			{
				if (qbertX > GameObject::getX())
					Character::move(0, scale, fpsScale);
				else
					Character::move(3, scale, fpsScale);
			}
			else
			{
				if (qbertX > GameObject::getX())
					Character::move(rand() % 2, scale, fpsScale);
				else
					Character::move(rand() % 2 + 2, scale, fpsScale);
			}	
			//move up or down
		}

	}
	return retVal;
}

void Snake::moveAnimate(__int8 state)
{
	if (isEgg)
	{
		if (state < 4)
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth, 0),
				sf::Vector2i(texWidth, texHeight)));
		else
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
				sf::Vector2i(texWidth, texHeight)));
	}
	else
	{
		switch (state)
		{
		default:
		case 0: // Up Right Jump
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		case 1: // Down Right Jump
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth * 5, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		case 2: // Down Left Jump
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth * 7, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		case 3: // Up Left Jump
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth * 3, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		case 4: // Up Right Land
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		case 5: // Down Right Land
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth * 4, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		case 6: // Down Left Land
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth * 6, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		case 7: // Up Left Land
			getSprite()->setTextureRect(sf::IntRect(sf::Vector2i(texWidth * 2, 0),
				sf::Vector2i(texWidth, texHeight)));
			break;
		}
	}
}



void Snake::findTarget( __int8 newTargetRow, __int16 newTargetX)
{
	qbertX = newTargetX;
	qbertRow = newTargetRow;
	return;
}

Snake::~Snake()
{ }


