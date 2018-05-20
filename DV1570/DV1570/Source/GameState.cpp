#include "GameState.h"

void GameState::_init(std::string pathToTexture, sf::IntRect area, sf::Vector2f position)
{
}

void GameState::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
}

GameState::GameState(std::string pathToTexture, sf::IntRect area, sf::Vector2f position)
{
	_init(pathToTexture, area, position);
}

GameState::~GameState()
{
}

void GameState::update(float dt)
{
}