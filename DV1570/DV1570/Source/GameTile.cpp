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
			scaleW = 40.0f / width;
			scaleH = 40.0f / height;
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
			scaleW = 40.0f / width;
			scaleH = 40.0f / height;
			m_sprite.setScale(sf::Vector2f(scaleW, scaleH));
			m_sprite.setPosition(sf::Vector2f(posX, posY));
			isDestructable = false;
		}
	}
}

void GameTile::onProjectileEvent(sf::Vector2f impactPoint, float blastRadius)
{
	if (this->m_sprite.getPosition() == impactPoint && this->isDestructable == true)
	{
		float radius = blastRadius;

		float left = impactPoint.x - radius;
		float right = impactPoint.x + radius;
		float top = impactPoint.y - radius;
		float bottom = impactPoint.y + radius;

		sf::Image image = m_texture.copyToImage();
		sf::Vector2u imagineSize = image.getSize();
		for (int i = top; i < bottom; i++)
		{
			for (int k = left; k < right; k++)
			{
				if ((i >= 0 && i < imagineSize.y) && (k >= 0 && k < imagineSize.y))
				{
					double dist = pow(impactPoint.x - k, 2) + pow(impactPoint.y - i, 2);
					if (dist <= pow(radius, 2))
					{
						sf::Color pixel = image.getPixel(k, i);
						pixel.a = 0;
						image.setPixel(k, i, pixel);
					}
				}
			}
		}
		m_texture.update(image);
		m_sprite.setTexture(m_texture);
	}
}

void GameTile::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(m_sprite, states);
}

