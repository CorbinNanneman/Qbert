#pragma once
/*
Allows for creation and managemnet of dynamic named floating point timers
*/

#include <vector>

class TimerManager
{
public:
	TimerManager( );

	void updateTimers( float incVal, bool paused );
	void erase( );

	bool addTimer( char *timerName, bool pauses );
	float checkTimer( char *timerName );
	void resetTimer( char *timerName );
	void removeTimer( char *timerName );

	~TimerManager( );

private:
	typedef struct
	{
		float time;
		char *name;
		bool pauses;
	} NamedTimer;

	std::vector< NamedTimer * > timers;
};
