#ifndef PLAYER_H
#define PLAYER_H

#include<SFML\Graphics.hpp>
#include<iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define LUA_PLAYER "Player"

using namespace std;
class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int spriteWidth;
	float speed = 180.0f;

	sf::Vector2i currentKeyFrame;
	sf::Vector2i keyFrameSize;
	float animationSpeed;
	float keyFrameDuration;

	string name;
	unsigned int hp;
public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	Player(const char* name, unsigned int hp, sf::Vector2f pos);
	~Player();
	void Move(float dt, lua_State * L);

	void update(float dt, lua_State * L);

	void setname(const char* name) { this->name = name; }
	const char* getname() { return this->name.c_str(); }
};
#endif

static int Player_new(lua_State* L)
{
	std::string name = lua_tostring(L, 1);
	unsigned int hp = lua_tonumber(L, 2);
	float x = lua_tonumber(L, 3);
	float y = lua_tonumber(L, 4);
	lua_pop(L, 4);
	*reinterpret_cast<Player**>(lua_newuserdata(L, sizeof(Player*))) = new Player(name.c_str(), hp, sf::Vector2f(x, y));
	luaL_setmetatable(L, LUA_PLAYER);
	return 1;
}

static int Player_delete(lua_State * L)
{
	delete *reinterpret_cast<Player**>(lua_touserdata(L, 1));
	return 0;
}

static int Player_setname(lua_State * L)
{
	(*reinterpret_cast<Player**>(luaL_checkudata(L, 1, LUA_PLAYER)))->setname(luaL_checkstring(L, 2));
	return 0;
}

static int Player_getname(lua_State * L)
{
	lua_pushstring(L, (*reinterpret_cast<Player**>(luaL_checkudata(L, 1, LUA_PLAYER)))->getname());
	return 1;
}

static void register_player(lua_State * L)
{
	lua_register(L, LUA_PLAYER, Player_new);
	luaL_newmetatable(L, LUA_PLAYER);
	lua_pushcfunction(L, Player_delete); lua_setfield(L, -2, "__gc");
	lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, Player_setname); lua_setfield(L, -2, "setname");
	lua_pushcfunction(L, Player_getname); lua_setfield(L, -2, "getname");
	lua_pop(L, 1);
}