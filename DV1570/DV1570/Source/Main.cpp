#include <SFML/Graphics.hpp>
#include "Game.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define LUA_GRAVITY -190


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF) | _CRTDBG_LEAK_CHECK_DF;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lira liide Liero");
	Game game;
	sf::Clock gameTime;
	
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	//register classes in Lua
	register_player(L);
	register_projectile(L);

	lua_pushstring(L, "Levels//TestLevel.txt");
	lua_setglobal(L, "LEVEL_PATH");

	if (!game.init(L, "Scripts//Game.lua"))
		goto Exit;
	
	lua_pushnumber(L, WINDOW_WIDTH);
	lua_setglobal(L, "WINDOW_WIDTH");
	lua_pushnumber(L, WINDOW_HEIGHT);
	lua_setglobal(L, "WINDOW_HEIGHT");
	lua_pushnumber(L, LUA_GRAVITY);
	lua_setglobal(L, "GRAVITY");


	while (window.isOpen())
	{
		//better safe than sorry - Ol' Gramps
		lua_pop(L, lua_gettop(L));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update()
		float dt = gameTime.restart().asSeconds();
		lua_pushnumber(L, dt);
		lua_setglobal(L, "FRAME_DELTA_TIME");

		game.Update(dt, window, L);

		// Draw()
		window.clear();
		window.draw(game);
		window.display();
	}
Exit:
	window.close();
	lua_close(L);

	std::cout << "\n\nPress anything to exit\n\n";
	std::getchar();
	
	return 0;
}