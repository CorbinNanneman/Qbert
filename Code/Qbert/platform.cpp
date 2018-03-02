#include "platform.h"

Platform::Platform( )
{ }


Platform::~Platform( )
{ }


// When only 2 cube textures are needed, newTexStrings[1] is set to NULL
void Platform::createMap( char* newTexStrings[3], double screenWidth, int scale )
{
	// *texStrings = *newTexStrings;
	texStrings[ 0 ] = newTexStrings[ 0 ];
	texStrings[ 1 ] = newTexStrings[ 1 ];
	texStrings[ 2 ] = newTexStrings[ 2 ];

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
			map[row][index].getSprite( )->setScale( scale, scale );
			int x = 32 * scale * (row * -.5 + index) + screenWidth / 2;
			int y = row * scale * 32 * .75 + 100;

			map[row][index].setX( x );
			map[row][index].setY( y );
		}
	}
}


void Platform::deleteMap()
{
	// Deallocate map storage
	for ( int i = 0; i < 7; i++ )
		delete[] map[i];
	delete[] map;
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
			if( cubeState = map[ row ][ index ].getState( ) < 2 )
				cubeState++;
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


Cube** Platform::getCubes( )
{
	return map;
}


bool Platform::win( )
{
	bool wrongCubeFound = false;
	for( int row = 0; !wrongCubeFound && row < 7; row++ )
		for( int index = 0; !wrongCubeFound && index < row + 1; index++ )
			if( map[ row ][ index ].getState( ) != 2 )
				wrongCubeFound = true;
	return !wrongCubeFound;
}
