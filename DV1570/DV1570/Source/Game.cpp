#include "Game.h"
#include <cmath>

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroundSprite, states);
	for (auto player : players)
	{
		player->draw(this->L, target, states);
	}
	
}

void Game::getPlayersFromLua(lua_State * L)
{
	lua_getglobal(L, "PLAYERS");
	Player *p = nullptr;
	std::cout << lua_topointer(L, -1) << std::endl;
	lua_pushnil(L);
	//loop through the table 
	while (lua_next(L, -2) != 0)
	{
		std::cout << lua_typename(L, lua_type(L, -1)) << std::endl;
		if (true)
		{
			std::cout << lua_topointer(L, -1) << std::endl;
			p = (Player*)lua_touserdata(L, -1);
			players.push_back(p);
		}
		lua_pop(L, 1);
	}

}

Game::Game()
{
	sf::String fileName = "..//Resources//bg.jpg";
	if (!backgroundTex.loadFromFile(fileName))
	{
		std::cout << "ERROR: Background image could not be loaded.\n---" << std::endl;
	}
	backgroundSprite.setTexture(backgroundTex);
}

bool Game::init(lua_State * L, std::string script)
{
	this->L = L;
	if (luaL_dofile(L, script.c_str()) != EXIT_SUCCESS)
	{
		printf(lua_tostring(L, -1));
		lua_pop(L, 1);
		return false;
	}
	//run the script that will instantiate all the Objects that were
	//created/added in the editor - let the script read and parse the level save file
	//get all the object pointers from the global object tables in Lua
	getPlayersFromLua(L);

	return true;
}

void Game::Update(float dt, const sf::Window &win, lua_State *L)
{
	
	for (auto player : players)
	{
		player->update(dt, L, win);
		if (Collision::pixelPerfectTest(player->getSprite(), player->getWep().getWepSprite(), 800 * 600))
		{
			cout << "COLLISION " << endl;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(win);
		int radius = 10;

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