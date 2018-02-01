#include "gameObject.h"

GameObject::GameObject()
{
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
}


GameObject::~GameObject()
{
}


void GameObject::update(int frame)
{
	x += vX;
	y += vY;
}


sf::Sprite GameObject::getSprite()
{
	return sprite;
}


void GameObject::setTexture(char* texPath)
{
	texture.loadFromFile(texPath);
}
