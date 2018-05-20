#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Editor.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define LUA_GRAVITY -190

#include "GameTile.h"

bool isRunning = true;
int choice = 0;
std::string levelFile = "";

void editorLoop();

void gameLoop();

sf::RenderWindow * window = nullptr;

enum STATES {
	EDITOR = 1,
	GAME = 2,
	EXIT = 3
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF) | _CRTDBG_LEAK_CHECK_DF;
	window = new sf::RenderWindow();
	while (isRunning)
	{
		system("cls");
		std::cout << "1. Editor" << std::endl;
		std::cout << "2. Game" << std::endl;
		std::cout << "3. Exit" << std::endl;
		cin >> choice;

		switch (choice)
		{
		case EDITOR:
			choice = 0;
			editorLoop();
			break;
		case GAME:
			choice = 0;
			system("cls");
			std::cin.ignore();
			std::cout << "Enter Game level filename (no extension): " << std::endl;
			std::getline(std::cin, levelFile);
			levelFile = "Levels//" + levelFile + ".txt";
			gameLoop();
			break;
		case EXIT:
			isRunning = false;
			break;
		default:
			break;
		}	
	}
	delete window;
	return 0;
}


void editorLoop()
{
	//create a window for the editor 
	window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Map Editor Liero");
	Editor editor(*window);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		editor.update(*window);
		window->clear();
		window->draw(editor);
		window->display();
	}
}

void gameLoop()
{
	Game game;
	sf::Clock gameTime;

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	//register classes in Lua
	register_player(L);
	register_spawnpoint(L);
	register_projectile(L);
	register_gametile(L);

	lua_pushstring(L, levelFile.c_str());
	lua_setglobal(L, "LEVEL_PATH");

	lua_pushnumber(L, WINDOW_WIDTH);
	lua_setglobal(L, "WINDOW_WIDTH");
	lua_pushnumber(L, WINDOW_HEIGHT);
	lua_setglobal(L, "WINDOW_HEIGHT");
	lua_pushnumber(L, LUA_GRAVITY);
	lua_setglobal(L, "GRAVITY");

	//try loading the game now
	if (!game.init(L))
	{
		lua_close(L);
		printf("\nFailed to create the Game :( \nPress Enter to continue");
		getchar();
		return;
	}

	window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Liero Alpha");

	while (window->isOpen())
	{
		//better safe than sorry - Ol' Gramps
		lua_pop(L, lua_gettop(L));
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		float dt = gameTime.restart().asSeconds();
		lua_pushnumber(L, dt);
		lua_setglobal(L, "FRAME_DELTA_TIME");

		game.Update(dt, *window, L);
		window->clear();
		window->draw(game);
		window->display();
	}
	lua_close(L);
}