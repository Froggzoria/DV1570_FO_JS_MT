#pragma once
#include "State.h"

class MainMenuState : public State
{
private:


	void _init(std::string pathToTexture, sf::IntRect area, sf::Vector2f position);

	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

public:
	MainMenuState(std::string pathToTexture, sf::IntRect area = sf::IntRect(), sf::Vector2f position = sf::Vector2f(0, 0));
	virtual~MainMenuState();

	void update(float dt);
};