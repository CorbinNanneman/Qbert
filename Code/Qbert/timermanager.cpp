#include "timermanager.h"

TimerManager::TimerManager( )
{ }


TimerManager::~TimerManager( )
{ 
	while( timers.size( ) > 0 )
		removeTimer( timers.at( 0 )->name );
}


void TimerManager::updateTimers( float incVal, bool paused )
{
	for( unsigned __int8 i = 0; i < timers.size( ); i++ )
		if( !paused || !timers.at( i )->pauses )
			timers.at( i )->time += incVal;
}


void TimerManager::erase( )
{
	while( timers.size( ) > 0 )
		removeTimer( timers.at( 0 )->name );
}


bool TimerManager::addTimer( char *timerName, bool pauses )
{
	bool created = false;
	// Create Timer if not already created
	if( checkTimer( timerName ) == -1.f )
	{
		NamedTimer *t = new NamedTimer;
		t->name = timerName;
		t->time = 0.f;
		t->pauses = pauses;
		timers.push_back( t );
		created = true;
	}

	return created;
}


float TimerManager::checkTimer( char *timerName )
{
	float time = -1.f; // If this is returned the timer does not exist

	for( unsigned __int8 i = 0; time == -1.f && i < timers.size( ); i++ )
		if( timers.at( i )->name == timerName )
			time = timers.at( i )->time;

	return time;
}


void TimerManager::resetTimer( char *timerName )
{
	bool reset = false;
	for( unsigned __int8 i = 0; !reset && i < timers.size( ); i++ )
	{
		if( timers.at( i )->name == timerName )
		{
			timers.at( i )->time = 0.f;
			reset = true;
		}
	}
}


void TimerManager::removeTimer( char *timerName )
{
	bool removed = false;
	for( unsigned int i = 0; !removed && i < timers.size( ); i++ )
	{
		if( timers.at( i )->name == timerName )
		{
			delete timers.at( i );
			timers.erase( timers.begin( ) + i );
			removed = true;
		}
	}
}

