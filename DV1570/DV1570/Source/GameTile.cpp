#include "GameTile.h"

GameTile::GameTile(std::string type, int posX, int posY)
{
	float width = 0.f;
	float height = 0.f;
	float scaleW, scaleH;

	if (type == SAND_TYPE)
	{

		if (!m_texture.loadFromFile(SAND_TYPE_PATH))
			printf("Failed to load Sand Tile texture\n");
		else
		{
			m_sprite.setTexture(m_texture);
			width = m_sprite.getLocalBounds().width;
			height = m_sprite.getLocalBounds().height;
			scaleW = 32.0f / width;
			scaleH = 32.0f / height;
			m_sprite.setScale(sf::Vector2f(scaleW, scaleH));
			m_sprite.setPosition(sf::Vector2f(posX, posY));
			isDestructable = true;
		}
	}
	else if (type == BOULDER_TYPE)
	{
		if (!m_texture.loadFromFile(BOULDER_TYPE_PATH))
			printf("Failed to load Boulder Tile texture\n");
		else
		{
			m_sprite.setTexture(m_texture);
			width = m_sprite.getLocalBounds().width;
			height = m_sprite.getLocalBounds().height;
			scaleW = 32.0f / width;
			scaleH = 32.0f / height;
			m_sprite.setScale(sf::Vector2f(scaleW, scaleH));
			m_sprite.setPosition(sf::Vector2f(posX, posY));
			isDestructable = false;
		}
	}
}

void GameTile::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(m_sprite, states);
}

