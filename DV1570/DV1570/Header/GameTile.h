#pragma once
#ifndef GAME_TILE_H
#define GAME_TILE_H

#include "SFML/Graphics.hpp"
#include <string>

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define LUA_GAMETILE "GameTile"

#define SAND_TYPE "Sand"
#define BOULDER_TYPE "Boulder"

#define SAND_TYPE_PATH "../Assets/platformerGraphicsDeluxe_Updated/Tiles/grassCenter.png"
#define BOULDER_TYPE_PATH "../Assets/platformerGraphicsDeluxe_Updated/Items/rock.png"

class GameTile : public sf::Drawable
{
public:
	GameTile(std::string type, int posX, int posY);
	~GameTile(){}

	sf::Sprite getSprite() { return m_sprite; }
	sf::FloatRect getBounds() { return m_sprite.getLocalBounds(); }
	void onProjectileEvent(sf::Vector2f impactPoint, float blastRadius);

	void draw(sf::RenderTarget &window, sf::RenderStates states) const;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	bool isDestructable;
};
#endif

static int GameTile_new(lua_State* L)
{
	std::string type = lua_tostring(L, 1);
	int x = lua_tonumber(L, 2);
	int y = lua_tonumber(L, 3);
	lua_pop(L, 3);

	GameTile* gT = new GameTile(type.c_str(), x, y);
	lua_pushlightuserdata(L, (void*)gT);
	luaL_setmetatable(L, LUA_GAMETILE);

	return 1;
}

static int GameTile_delete(lua_State* L)
{
	delete (GameTile*)lua_touserdata(L, 1);
	return 0;
}

static void register_gametile(lua_State* L)
{
	// Register the type in LUA with the constructor
	lua_register(L, LUA_GAMETILE, GameTile_new);

	// Create a new metatable for this type
	luaL_newmetatable(L, LUA_GAMETILE);
	lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");

	// Push all functions to this metatable and assign the value (name of functions in LUA)
	lua_pushcfunction(L, GameTile_delete); lua_setfield(L, -2, "__gc");
	lua_pop(L, 1);
}