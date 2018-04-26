#pragma once
#include "State.h"

class GameState : public State
{
private:
	void _init();

public:
	GameState();
	~GameState();

	void update(float dt);
	void draw();
};