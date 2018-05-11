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
	
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	register_player(L);
	lua_pushstring(L, "Levels//TestLevel.txt");
	lua_setglobal(L, "LEVEL_PATH");

	if (!game.init(L, "Scripts//Game.lua"))
		goto Exit;
	luaL_dofile(L, "Scripts//Player.lua");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update()
		game.Update(gameTime.restart().asSeconds(), window, L);

		// Draw()
		window.clear();
		window.draw(game);
		window.display();
	}
Exit:
	std::cout << "\n\nPress anything to exit\n\n";
	std::getchar();
	lua_close(L);
	return 0;
}