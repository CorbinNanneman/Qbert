/*==============================================================*\
|                                                                |
| Program: Qbert                                                 |
|                                                                |
| Breif: Classic arcade game recreated in C++                    |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| Leader: Corbin Nanneman                                        |
|                                                                |
| Program Authors: Greg Francis, Ben Ewing, Corbin Nanneman      |
|                                                                |
|                                                                |
|                                                                |
| -------------------------------------------------------------- |
|                                                                |
| Author: Greg Francis                                           |
|                                                                |
| Date Created: February 12th, 2018                              |
|                                                                |
| Date Last Modified: Feburary 21th, 2018 | 7:32 PM              |
|                                                                |
\*==============================================================*/

#include "statemanager.h"
	
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
