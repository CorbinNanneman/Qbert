#include "gameobject.h"
#include <SFML\Graphics.hpp>

GameObject::GameObject( float scale )
{
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
	texWidth = 0;
	texHeight = 0;
	sprite.setScale( scale, scale );
}

GameObject::GameObject( )
{
	x = 0;
	y = 0;
	vX = 0;
	vY = 0;
	texWidth = 0;
	texHeight = 0;
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


bool GameObject::isOffScreen( __int16 screenWidth, __int16 screenHeight, float scale )
{
	// Store texture size calculations
	__int16 halfTexWidth = texWidth * scale / 2,
			halfTexHeight = texHeight * scale / 2;
	return x + halfTexWidth < 0 || x - halfTexWidth > screenWidth || 
		y + halfTexHeight < 0 || y + halfTexHeight  > screenHeight;
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



sf::Sprite* GameObject::getSpritePtr( )
{
	return &sprite;
}


void GameObject::setTexture( char* texPath, __int16 newTexWidth, __int16 newTexHeight)
{
	// Update Texture
	texture.loadFromFile( texPath );
	sprite.setTexture( texture );
	texWidth = newTexWidth;
	texHeight = newTexHeight;

	// Update view rectangle and center
	updateTexRect( 0, 0 );
	sprite.setOrigin( texWidth / 2, texHeight / 2 );
}


void GameObject::updateTexRect( __int16 xFrame, __int16 yFrame )
{
	sprite.setTextureRect( 
		sf::IntRect( xFrame * texWidth, yFrame * texHeight, texWidth, texHeight ) );
}
