# Q\*BERT

It's Q\*Bert, written in C++, using the SFML graphics library.

### To those resuming work on this project in the future:

The core mechanics of the game, like characters, their movement, and the overlay, are mostly complete.

The score needs to be implemented, and it will be drawn as part of Overlay (see StateManager.h for relevant methods)
The platform behavior is not complete for each level, and a framework is exists in the Platform class for dealing with cube behavior.
StateManager.cpp is going to hold the majority of the logic. StateTransition( State ) is called whenever the game transfers from one state to another. The actual state in StateManager is not updated until end of function, so you can do different things based on previous state. Disks haven't been created yet. The FPS system works in that FPS is calculated every frame, and targetFPS is a value for regulating velocites in GameObjects, among other important things. Don't mess with the value of targetFPS as I'm not sure what would happen, and it does not actually affect FPS. TimerManager is a utility class for dynamic management of float timers (1.25 = 1.25 seconds). The other states, like the title screen and leaderboard, need to be implemented.

Good luck, have fun, make Lil Q happy.
