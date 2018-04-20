#include "StateManager.h"
	
int main()
{
	srand( (size_t)time( NULL ) );

	StateManager game;

	while( game.isOpen( ) )
	{
		game.clear( );
		game.update( );
		game.display( );
	}

	return 0;
}
