#include "Game.h"
#include <cmath>

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

void Game::Update(float dt, const sf::Window &win, lua_State *L)
{
	player.update(dt, L);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(win);
		int radius = 30;

		int left = pos.x - radius;
		int right = pos.x + radius;
		int top = pos.y - radius;
		int bottom = pos.y + radius;

		sf::Image image = backgroundTex.copyToImage();
		sf::Vector2u imageSize = image.getSize();
		for (int i = top; i < bottom; i++)
		{
			for (int k = left; k < right; k++)
			{
				if ((i >= 0 && i < imageSize.y) && (k >= 0 && k < imageSize.x))
				{
					double dist = pow(pos.x - k, 2) + pow(pos.y - i, 2);
					if (dist <= pow(radius, 2))
					{
						sf::Color pixel = image.getPixel(k, i);
						pixel.a = 0;
						image.setPixel(k, i, pixel);
					}
				}
			}
		}
		backgroundTex.update(image);
		backgroundSprite.setTexture(backgroundTex);
	}
}