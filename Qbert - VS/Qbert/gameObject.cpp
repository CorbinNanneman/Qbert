#include "gameObject.h"

#include <SFML\Graphics.hpp>

GameObject::GameObject()
{
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
	texRectWidth = 8;
	texRectHeight = 8;
}


GameObject::~GameObject()
{
}


void GameObject::update(int frame)
{
	x += vX;
	y += vY;
	sprite.setPosition(x, y);
}


void GameObject::setX(int newX)
{
	x = newX;
}


void GameObject::setY(int newY)
{
	y = newY;
}


void GameObject::setVX(int newVX)
{
	vX = newVX;
}


void GameObject::setVY(int newVY)
{
	vY = newVY;
}


int GameObject::getX()
{
	return x;
}


int GameObject::getY()
{
	return y;
}


sf::Sprite* GameObject::getSprite()
{
	return &sprite;
}


void GameObject::setTexture(char* texPath, //texture stuff here)
{
	texture.loadFromFile(texPath);
	sprite.se
}
