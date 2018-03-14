#pragma once
// Date Last Modified: March 14th, 2018

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject
{
public:
	GameObject( );
	GameObject( float scale );

	virtual void update( );
	bool isOffScreen( __int16 screenWidth, __int16 screenHeight, float scale );

	sf::Sprite* getSprite( );
	void setTexture( char* texPath, __int16 texWidth, __int16 texHeight );

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
	__int16 texWidth, texHeight;
private:
	float x, y, vX, vY;
	sf::Texture texture;
	sf::Sprite sprite;
};
