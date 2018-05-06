#include "Game.h"

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroundSprite, states);
	player.draw(target, states);
}

Game::Game() : player("charlie", 100, sf::Vector2f(0, 0))
{
	sf::String fileName = "..//Resources//bg.jpg";
	if (!backgroundTex.loadFromFile(fileName))
	{
		std::cout << "ERROR: Background image could not be loaded.\n---" << std::endl;
	}
	backgroundSprite.setTexture(backgroundTex);
}

void Game::Update(float dt)
{
	player.update(dt);
}