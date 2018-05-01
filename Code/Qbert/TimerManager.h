#pragma once
/*
Allows for creation and managemnet of dynamic named floating point timers
*/

#include <vector>

class TimerManager
{
public:
	TimerManager( );

	void updateTimers( float incVal, unsigned __int8 pauseLevel );
	void erase( );

	bool addTimer( char *timerName, unsigned __int8 pauseLevel );
	float checkTimer( char *timerName );
	void resetTimer( char *timerName );
	void removeTimer( char *timerName );

	~TimerManager( );

private:
	typedef struct
	{
		float time;
		char *name;
		unsigned __int8 pauseLevel;
	} NamedTimer;

	std::vector< NamedTimer * > timers;
};
