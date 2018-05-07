#include "GameState.h"

void GameState::_init(std::string pathToTexture, sf::IntRect area, sf::Vector2f position)
{
}

GameState::GameState(std::string pathToTexture, sf::IntRect area, sf::Vector2f position)
{
	this->_init(pathToTexture, area, position);
}

GameState::~GameState()
{
}

void GameState::update(float dt)
{
}

void GameState::draw() const
{

}
