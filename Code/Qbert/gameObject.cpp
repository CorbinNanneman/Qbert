#include "gameObject.h"
#include <SFML\Graphics.hpp>

GameObject::GameObject( float scale )
{
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
	sprite.setScale( scale, scale );
}

GameObject::GameObject( )
{
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
	sprite.setScale( 1, 1 );
}


GameObject::~GameObject( )
{ }


void GameObject::update( )
{
	x += vX;
	y += vY;
	sprite.setPosition( x, y );
}


void GameObject::setX( float newX )
{
	x = newX;
	sprite.setPosition( sf::Vector2f( x, y ) );
}


void GameObject::setY( float newY )
{
	y = newY;
	sprite.setPosition( sf::Vector2f( x, y ) );
}


void GameObject::setVX( float newVX )
{
	vX = newVX;
}


void GameObject::setVY( float newVY )
{
	vY = newVY;
}


float GameObject::getX( )
{
	return x;
}


float GameObject::getY( )
{
	return y;
}


float GameObject::getVX( )
{
	return vX;
}


float GameObject::getVY( )
{
	return vY;
}



sf::Sprite* GameObject::getSprite( )
{
	return &sprite;
}


void GameObject::setTexture( char* texPath, __int16 texWidth, __int16 texHeight)
{
	texture.loadFromFile( texPath );
	sprite.setTexture( texture );
	sprite.setTextureRect( sf::IntRect( sf::Vector2i(0, 0), sf::Vector2i(texWidth, texHeight) ) );
	sprite.setOrigin( texWidth / 2, texHeight / 2 );
}
