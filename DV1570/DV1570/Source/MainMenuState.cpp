#include "MainMenuState.h"

void MainMenuState::_init(std::string pathToTexture, sf::IntRect area, sf::Vector2f position)
{
}

void MainMenuState::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
}

MainMenuState::MainMenuState(std::string pathToTexture, sf::IntRect area, sf::Vector2f position)
{
	_init(pathToTexture, area, position);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update(float dt)
{
}