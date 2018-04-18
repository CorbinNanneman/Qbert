#include "StateManager.h"
	
int main()
{
	srand( time( NULL ) );

	StateManager game;

	while( game.isOpen( ) )
	{
		game.clear( );
		game.update( );
		game.display( );
	}

	return 0;
}
