#include "Game.h"

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!mBackgroundTex.loadFromFile("../Rescoures/background.png"))
	{
		std::cout << "ERROR: Background image could not be loaded.\n---" << std::endl;
	}
	mBackgroundSprite.setTexture(mBackgroundTex);
}

Game::Game()
{
}

void Game::Update(float dt)
{
}
