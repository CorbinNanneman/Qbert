#include "Platform.h"

Platform::Platform( )
{ 
	map = nullptr;
}


Platform::~Platform( )
{ }


void Platform::createMap( __int8 level, __int8 round, __int16 screenWidth, float scale )
{
	setTextures( level, round );

	// Allocate map storage
	map = new Cube*[7];
	for( int i = 0; i < 7; i++ )
		map[i] = new Cube[ i + 1 ];

	// Initialize and position cubes in map
	for ( int row = 0; row < 7; row++ )
	{
		for ( int index = 0; index < row + 1; index++ )
		{
			// Initialize textures
			map[row][index].setTexture( texStrings[0], 32, 32 );
			
			// Cube coordinate calculations
			map[row][index].getSpritePtr( )->setScale( scale, scale );
			float x = 32 * scale * (row * -.5f + index) + screenWidth / 2,
				  y = row * scale * 32 * .75f + 50 * scale;

			map[row][index].setX( x );
			map[row][index].setY( y );
		}
	}
}


void Platform::deleteMap()
{
	if( map != nullptr )
	{
		for ( int i = 0; i < 7; i++ )
			delete[] map[i];
		delete[] map;
	}
}


void Platform::changeCube( __int8 row, __int8 index, __int8 changeType, __int8 level )
{
	// Determine correct new texture for targeted cube, based off level and changeType
	__int8 cubeState = -1;
	switch( changeType )
	{
	case 0: // Q*Bert lands
		switch( level )
		{
		case 1:
			if( map[ row ][ index ].getState( ) == 0 )
				cubeState = 2;
			break;
		case 2:
			if( ( cubeState = map[ row ][ index ].getState( ) ) < 2 )
				cubeState++;
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			if( ( cubeState = map[ row ][ index ].getState( ) + 1 ) > 2 ) 
				cubeState = 0;
			break;
		default:
			break;
		}
		break;
	case 1: // Sam lands
		switch( level )
		{
		case 1:
			if( map[ row ][ index ].getState( ) == 2 )
				cubeState = 0;
			break;
		case 2:
			if( cubeState = map[ row ][ index ].getState( ) > 0 )
				cubeState--;
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
		break;
	case 2: // Slick lands
		cubeState = 0;
		break;
	default:
		break;
	}

	if( cubeState != -1 )
	{
		map[row][index].setTexture( texStrings[cubeState], 32, 32 );
		map[row][index].setState( cubeState );
	}
}


void Platform::setTextures( __int8 level, __int8 round )
{
	switch( level * round )
	{
	default:
	case 1: // Level 1 Round 1
		texStrings[ 0 ] = "./images/blueBlue.png";
		texStrings[ 1 ] = "./images/bluePink.png";
		texStrings[ 2 ] = "./images/blueYellow.png";
		break;
	case 2:// Level 1 Round 2
		texStrings[ 0 ] = "./images/greyGrey.png";
		texStrings[ 1 ] = "./images/greyBlue.png";
		texStrings[ 2 ] = "./images/greyWhite.png";
		break;
	case 3:// Level 1 Round 3
		break;
	case 4:// Level 1 Round 4
		break;
	case 5:// Level 2 Round 1
		break;
	case 6:// Level 2 Round 2
		break;
	case 7:// Level 2 Round 3
		break;
	case 8:// Level 2 Round 4
		break;
	case 9:// Level 3 Round 1
		break;
	case 10:// Level 3 Round 2
		break;
	case 11:// Level 3 Round 3
		break;
	case 12:// Level 3 Round 4
		break;
	case 13:// Level 4 Round 1
		break;
	case 14:// Level 4 Round 2
		break;
	case 15:// Level 4 Round 3
		break;
	case 16:// Level 4 Round 4
		break;
	case 17:// Level 5 Round 1
		break;
	case 18:// Level 5 Round 2
		break;
	case 19:// Level 5 Round 3
		break;
	case 20:// Level 5 Round 4
		break;
	}
}


Cube** Platform::getCubes( )
{
	return map;
}


bool Platform::isComplete( )
{
	bool wrongCubeFound = false;
	for( int row = 0; !wrongCubeFound && row < 7; row++ )
		for( int index = 0; !wrongCubeFound && index < row + 1; index++ )
			if( map[ row ][ index ].getState( ) != 2 )
				wrongCubeFound = true;
	return !wrongCubeFound;
}
