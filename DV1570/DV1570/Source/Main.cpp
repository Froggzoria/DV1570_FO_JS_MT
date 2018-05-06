#include <SFML/Graphics.hpp>
#include "Game.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF) | _CRTDBG_LEAK_CHECK_DF;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Window");
	Game game;
	sf::Clock gameTime;

	//lua_State *L = luaL_newstate();
	//luaL_openlibs(L);

	//luaL_dofile(L, "Scripts//Player.lua");
	//lua_getglobal(L, "printMsg");
	//lua_pushstring(L, "hello from lua");
	//lua_pushnumber(L, 5);
	//lua_pcall(L, 2, 0, 0);

	//lua_close(L);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update()
		game.Update(gameTime.restart().asSeconds());

		// Draw()
		window.clear();
		window.draw(game);
		window.display();
	}
	return 0;
}