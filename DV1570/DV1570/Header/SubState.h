#pragma once
#include "Object.h"

class SubState
{
private:
	Object m_substateObject;

	void _init();

public:
	SubState();
	~SubState();

	void update(float dt);
	void draw();
};