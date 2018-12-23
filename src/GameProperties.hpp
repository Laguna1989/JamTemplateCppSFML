#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

class GP
{
public:
	GP() = delete;
	static float playerMovementSpeed() { return 200; }
	static float playerAcceleration() {return 400; }
	static float playerShotTimer() { return 0.9f; }
};

#endif
