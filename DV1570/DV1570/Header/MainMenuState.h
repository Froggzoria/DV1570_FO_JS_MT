#pragma once
#include "State.h"

class MainMenuState : public State
{
private:


	void _init();

public:
	MainMenuState();
	~MainMenuState();

	void update(float dt);
	void draw();
};