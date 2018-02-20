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

	virtual void update( );

	void setX( int newX );
	void setY( int newY );
	void setVX( int newVX );
	void setVY( int newVY );
	int getX( );
	int getY( );

	sf::Sprite* getSprite( );
	void setTexture( char* texPath, uint8_t texWidth, uint8_t texHeight );

	~GameObject();
private:
	float x, 
		  y, 
		  vX, 
		  vY;
	sf::Texture texture;
	sf::Sprite sprite;
};
