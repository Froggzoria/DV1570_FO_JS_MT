#pragma once

#include <SFML\Graphics.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define LUA_SPAWNPOINT "SpawnPoint"
#define LUA_SPAWNPOINT_GETPOS "GetPos"

class SpawnPoint
{
private:
	sf::Vector2f m_pos;

public:
	SpawnPoint(sf::Vector2f pos)
	{
		m_pos = pos;
	}
	virtual ~SpawnPoint() {}

	sf::Vector2f getPos() const { return m_pos; }
};

static int SpawnPoint_new(lua_State* L)
{
	float xPos = lua_tonumber(L, 1);
	float yPos = lua_tonumber(L, 1);

	lua_pop(L, 2);

	SpawnPoint* sP = new SpawnPoint(sf::Vector2f(xPos, yPos));
	lua_pushlightuserdata(L, (void*)sP);
	luaL_setmetatable(L, LUA_SPAWNPOINT);

	return 1;
}

static int SpawnPoint_delete(lua_State* L)
{
	delete (SpawnPoint*)lua_touserdata(L, 1);
	return 0;
}

static int SpawnPoint_getpos(lua_State* L)
{
	SpawnPoint* sP = (SpawnPoint*)lua_touserdata(L, 1);
	if (sP == NULL)
		return 0;

	lua_pushnumber(L, sP->getPos().x);
	lua_pushnumber(L, sP->getPos().y);

	return 2;
}

static void register_spawnpoint(lua_State* L)
{
	// Register the type in LUA with the constructor
	lua_register(L, LUA_SPAWNPOINT, SpawnPoint_new);

	// Create a new metatable for this type
	luaL_newmetatable(L, LUA_SPAWNPOINT);
	lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");

	// Push all functions to this metatable and assign the value (name of functions in LUA)
	lua_pushcfunction(L, SpawnPoint_delete); lua_setfield(L, -2, "__gc");
	lua_pushcfunction(L, SpawnPoint_getpos); lua_setfield(L, -2, LUA_SPAWNPOINT_GETPOS);

	lua_pop(L, 1);
}