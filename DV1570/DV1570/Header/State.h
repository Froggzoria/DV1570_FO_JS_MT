#pragma once
#include "SubState.h"
#include <stack>

class State
{
private:
	bool m_exitState = false;
	std::stack<SubState> m_substates;

	virtual void _init() = 0;
public:

	State() {}
	virtual ~State() {}

	virtual void update(float dt) = 0;
	virtual void draw() = 0;
};