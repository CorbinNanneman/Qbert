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
	GameObject( );
	GameObject( float scale );

	void update( );

	void setX( float newX );
	void setY( float newY );
	void setVX( float newVX );
	void setVY( float newVY );
	float getX( );
	float getY( );
	float getVX( );
	float getVY( );

	sf::Sprite* getSprite( );
	void setTexture( char* texPath, __int16 texWidth, __int16 texHeight );

	~GameObject( );
private:
	float x, y, vX, vY;
	sf::Texture texture;
	sf::Sprite sprite;
};
