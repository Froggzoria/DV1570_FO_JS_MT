#pragma once
#include "SubState.h"
#include <stack>

class State
{
private:
	virtual void _init() = 0;

protected:
	bool m_exitState;
	std::stack<SubState> m_substates;
	Object m_stateObject;

public:

	State() { m_exitState = false; }
	virtual ~State() {}

	virtual void update(float dt) = 0;
	virtual void draw() = 0;
};