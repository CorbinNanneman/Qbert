#include "Platform.h"

Platform::Platform( )
{ 
	map = nullptr;
}


Platform::~Platform( )
{ }


// When only 2 cube textures are needed, newTexStrings[1] is set to NULL
void Platform::createMap( char const *newTexStrings[3], __int16 screenWidth, float scale )
{
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
			map[row][index].getSpritePtr( )->setScale( scale, scale );
			float x = 32 * scale * (row * -.5f + index) + screenWidth / 2,
				  y = row * scale * 32 * .75f + 50 * scale;

			map[row][index].setX( x );
			map[row][index].setY( y );
		}
	}

	for (int i = 0; i < 3/* <- # of disk */; i++)
	{
		disks.push_back(new Disk(scale));

		bool occupied;
		do
		{
			disks.at(i)->randomizePos();

			occupied = false;
			for (int j = 0; !occupied && j < disks.size() - 1; j++)
				if (disks.at(i)->getIndex() == disks.at(j)->getIndex()
					&& disks.at(i)->getRow() == disks.at(j)->getRow())
					occupied = true;
		} while (occupied);

		// create disk
		// are positions equal to positions other disks?
		//YES: you must die, and be recreated
		//NO: carry on then
	}
}


void Platform::deleteMap()
{
	// Avoid doing bad things
	if( !deleted )
	{
		// Deallocate map storage
		for ( int i = 0; i < 7; i++ )
			delete[] map[i];
		delete[] map;

		for (int i = 0; i < disks.size(); i++)
			delete disks.at(i);
		

		deleted = true;
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


Cube** Platform::getCubes( )
{
	return map;
}

//make a get disks function


bool Platform::isComplete( )
{
	bool wrongCubeFound = false;
	for( int row = 0; !wrongCubeFound && row < 7; row++ )
		for( int index = 0; !wrongCubeFound && index < row + 1; index++ )
			if( map[ row ][ index ].getState( ) != 2 )
				wrongCubeFound = true;
	return !wrongCubeFound;
}
