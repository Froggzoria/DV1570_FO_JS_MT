#pragma once
#include "SubState.h"
#include <stack>

class State
{
private:
	virtual void _init(std::string pathToTexture, sf::IntRect area, sf::Vector2f position) = 0;

protected:
	bool m_exitState;
	std::stack<SubState> m_substates;
	Object m_stateObject;

public:

	State() { m_exitState = false; }
	virtual ~State() {}

	virtual void update(float dt) = 0;
	virtual void draw() const = 0;
};