#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject
{
public:
	GameObject( float scale = 1, __int8 tAFrames = 0, float aDelay = 0.f );

	void update( float fpsScale, float incVal );
	virtual void update( float fpsScale );

	bool isOffScreen( __int16 screenWidth, __int16 screenHeight, float scale );

	sf::Sprite* getSpritePtr( );
	void setTexture( const char* texPath, __int16 texWidth, __int16 texHeight );
	void setTexRect( __int16 xFrame, __int16 yFrame );

	void setX( float newX );
	void setY( float newY );
	void setVX( float newVX );
	void setVY( float newVY );
	void setZ( __int16 newZ );
	
	float getX( );
	float getY( );
	float getVX( );
	float getVY( );
	__int16 getZ( );

	// Allows children to adjust position of parent's inherited movemnt patterns
	void setXOffset( float nexXOffset );
	void setYOffset( float newYOffset );
	float getXOffset( );
	float getYOffset( );

	void cycleAnimation( );

	~GameObject( );
protected:
	
private:
	float x, y, targetVX, targetVY, z, xOffset, yOffset;
	__int16 texWidth, texHeight;
	sf::Texture texture;
	sf::Sprite sprite;
	__int8 animFrame, totalAnimFrames;
	float animTimer, animDelay;
};
