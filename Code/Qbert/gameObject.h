#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject
{
public:
	GameObject( );
	GameObject( float scale );

	virtual void update( );
	bool isOffScreen( __int16 screenWidth, __int16 screenHeight, float scale );

	sf::Sprite* getSpritePtr( );
	void setTexture( const char* texPath, __int16 texWidth, __int16 texHeight );
	void setTexRect( __int16 xFrame, __int16 yFrame );

	void setX( float newX );
	void setY( float newY );
	void setVX( float newVX );
	void setVY( float newVY );
	float getX( );
	float getY( );
	float getVX( );
	float getVY( );

	~GameObject( );
protected:
	
private:
	float x, y, vX, vY;
	__int16 texWidth, texHeight;
	sf::Texture texture;
	sf::Sprite sprite;
};
