#pragma once
#include "State.h"

class MainMenuState : public State
{
private:


	void _init(std::string pathToTexture, sf::IntRect area, sf::Vector2f position);

public:
	MainMenuState(std::string pathToTexture, sf::IntRect area = sf::IntRect(), sf::Vector2f position = sf::Vector2f(0, 0));
	~MainMenuState();

	void update(float dt);
	void draw() const;
};