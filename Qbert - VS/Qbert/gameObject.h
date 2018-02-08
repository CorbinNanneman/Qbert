#pragma once
/*
Date Created:
	Feburary 1st, 2018
Date Last Modified:
	Feburary 1st, 2018 | 12:03PM
*/

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject
{
public:
	GameObject();

	virtual void update(int frame);
	void setX(int newX);
	void setY(int newY);
	void setVX(int newVX);
	void setVY(int newVY);
	int getX();
	int getY();

	sf::Sprite* getSprite();
	void setTexture(char* texPath);

	~GameObject();
protected:
	int texRectWidth, texRectHeight;
private:
	double x, y, vX, vY;
	sf::Texture texture;
	sf::Sprite sprite;
};
