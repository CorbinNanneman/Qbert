#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject
{
public:
	GameObject( float scale = 1 );

	void update( float incVal );
	virtual void update( );

	bool isOffScreen( __int16 screenWidth, __int16 screenHeight, float scale );

	sf::Sprite* getSpritePtr( );
	void setTexture( const char* texPath, __int16 texWidth, __int16 texHeight );
	void setTexRect( __int16 xFrame, __int16 yFrame );

	void setX( float newX );
	void setY( float newY );
	void setVX( float newVX );
	void setVY( float newVY );
	void setZ( __int8 newZ );

	float getX( );
	float getY( );
	float getVX( );
	float getVY( );
	__int8 getZ( );

	void cycleAnimation( );

	~GameObject( );
protected:
	
private:
	float x, y, vX, vY;
	__int16 texWidth, texHeight;
	sf::Texture texture;
	sf::Sprite sprite;
	__int8 animFrame, totalAnimFrames, animTimer, animDelay,
		   zIndex;
};
