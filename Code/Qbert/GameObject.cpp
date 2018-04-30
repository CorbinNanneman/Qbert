#include "GameObject.h"
#include <SFML/Graphics/Rect.hpp>

GameObject::GameObject( float scale, __int8 tAFrames, float aDelay )
{
	x = 0;
	y = 0;
	targetVX = 0;
	targetVY = 0;
	z = 0;
	xOffset = 0;
	yOffset = 0;

	texWidth = 0;
	texHeight = 0;
	animFrame = 0;
	totalAnimFrames = tAFrames;
	animDelay = aDelay;
	sprite.setScale( scale, scale );
}


GameObject::~GameObject( )
{ }


// Update for auto-animated objects
void GameObject::update( float fpsScale, float incVal )
{
	animTimer += incVal;
	if( animTimer > animDelay )
	{
		cycleAnimation( );
		animTimer = 0.f;
	}
	update( fpsScale );
}


void GameObject::update( float fpsScale )
{
	// Target VX is modified to account for fps
	x += targetVX * fpsScale;
	y += targetVY * fpsScale;
	sprite.setPosition( x, y );
}


bool GameObject::isOffScreen( __int16 screenWidth, __int16 screenHeight, float scale )
{
	// Store texture size calculations
	__int16 halfTexWidth = texWidth * scale / 2,
			halfTexHeight = texHeight * scale / 2;
	return x + halfTexWidth < 0 || x - halfTexWidth > screenWidth || 
		y + halfTexHeight < 0 || y - halfTexHeight  > screenHeight;
}


void GameObject::setX( float newX )
{
	x = newX + xOffset;
	sprite.setPosition( x, y );
}


void GameObject::setY( float newY )
{
	y = newY + yOffset;
	sprite.setPosition( x, y );
}


void GameObject::setVX( float newVX )
{
	targetVX = newVX;
}


void GameObject::setVY( float newVY )
{
	targetVY = newVY;
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
	return targetVX;
}


float GameObject::getVY( )
{
	return targetVY;
}


__int16 GameObject::getZ( )
{
	return z;
}


void GameObject::setZ( __int16 newZ )
{
	z = newZ;
}


// Allows children to adjust position of parent's inherited movemnt patterns
void GameObject::setXOffset( float newXOffset )
{
	xOffset = newXOffset;
}


void GameObject::setYOffset( float newYOffset )
{
	yOffset = newYOffset;
}


float GameObject::getXOffset( )
{
	return xOffset;
}


float GameObject::getYOffset( )
{
	return yOffset;
}


sf::Sprite* GameObject::getSpritePtr( )
{
	return &sprite;
}


void GameObject::setTexture( const char* texPath, __int16 newTexWidth, __int16 newTexHeight)
{
	// Update Texture
	texture.loadFromFile( texPath );
	sprite.setTexture( texture );
	texWidth = newTexWidth;
	texHeight = newTexHeight;

	// Update view rectangle and center
	setTexRect( 0, 0 );
	sprite.setOrigin( texWidth / 2, texHeight / 2 );
}


void GameObject::setTexRect( __int16 xFrame, __int16 yFrame )
{
	sprite.setTextureRect( 
		sf::IntRect( xFrame * texWidth, yFrame * texHeight, texWidth, texHeight ) );
}


void GameObject::cycleAnimation( )
{
	// Animations are expected in a LtR format
	if( ++animFrame >= totalAnimFrames )
		animFrame = 0;
	setTexRect( animFrame, 0 );
}
