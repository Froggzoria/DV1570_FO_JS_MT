#pragma once
#include "Object.h"

class SubState
{
private:
	Object m_substateObject;

	void _init(std::string pathToTexture, sf::IntRect area, sf::Vector2f position);

public:
	SubState(std::string pathToTexture, sf::IntRect area = sf::IntRect(), sf::Vector2f position = sf::Vector2f(0, 0));
	~SubState();

	void update(float dt);
	void draw();
};