#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML\Graphics.hpp>
#include"Player.h"
#include"Collision.h"
#include <vector>

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class Game : public sf::Drawable
{
private:
	sf::Texture backgroundTex;
	sf::Sprite backgroundSprite;
	std::vector<Player*> players;
	lua_State * L;


	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void getPlayersFromLua(lua_State * L);
public:
	Game();

	bool init(lua_State * L, std::string script);

	void Update(float dt, const sf::Window &win, lua_State *L);
};
#endif