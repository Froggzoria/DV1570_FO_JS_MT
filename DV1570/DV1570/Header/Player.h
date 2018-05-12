#ifndef PLAYER_H
#define PLAYER_H

#include<SFML\Graphics.hpp>
#include<iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

//name of constructor and all player functions in Lua
#define LUA_PLAYER "Player"
#define LUA_PLAYER_SETNAME "SetName"
#define LUA_PLAYER_GETNAME "GetName"
#define LUA_PLAYER_SETANIKEY "SetAniKey"
#define LUA_PLAYER_GETANIKEY "GetAniKey"
#define LUA_PLAYER_GETKEYFRAMEDUR "GetKeyFrameDur"
#define LUA_PLAYER_SETKEYFRAMEDUR "SetKeyFrameDur"
#define LUA_PLAYER_SETMS "SetMS"
#define LUA_PLAYER_GETMS "GetMS"
#define LUA_PLAYER_SETHP "SetHP"
#define LUA_PLAYER_GETHP "GetHP"
#define LUA_PLAYER_SETDISVECT "SetDisVec"
#define LUA_PLAYER_GETDISVECT "GetDisVec"
#define LUA_PLAYER_MOVESPRITE "MoveSprite"

using namespace std;
class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int spriteWidth;
	float speed = 180.0f;

	sf::Vector2f displacement;
	sf::Vector2i currentKeyFrame;
	sf::Vector2i keyFrameSize;
	float animationSpeed;
	float keyFrameDuration;

	string name;
	unsigned int hp;
public:
	//to modify this object in Lua we create set and get functions
	//for all the members we want to be modified
	//--------SET---------
	void setname(const char* name) { this->name = name; }
	void setAnimationKey(float key) { currentKeyFrame.y = key; }
	void setKeyFrameDur(float dur) { keyFrameDuration = dur; }
	void setMoveSpeed(float ms) { speed = ms; }
	void setHP(unsigned int hp) { this->hp = hp; }
	void moveSprite(sf::Vector2f displacement) { this->sprite.move(displacement); }

	//--------GET---------
	const char* getname() { return this->name.c_str(); }
	float getAnimationKey() { return this->currentKeyFrame.y; }
	float getKeyFrameDur() { return this->keyFrameDuration; }
	float getMoveSpeed() { return this->speed; }
	unsigned int getHP() { return this->hp; }

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	Player(const char* name, unsigned int hp, sf::Vector2f pos);
	~Player();
	void Move(lua_State * L);
	void update(float dt, lua_State * L);
	
};
#endif

static int Player_new(lua_State* L)
{
	std::string name = lua_tostring(L, 1);
	unsigned int hp = lua_tonumber(L, 2);
	float x = lua_tonumber(L, 3);
	float y = lua_tonumber(L, 4);
	lua_pop(L, 4);
	
	Player * p = new Player(name.c_str(), hp, sf::Vector2f(x, y));
	lua_pushlightuserdata(L, (void*)p);
	luaL_setmetatable(L, LUA_PLAYER);

	return 1;
}

static int Player_delete(lua_State * L)
{
	delete (Player*)lua_touserdata(L, 1);
	return 0;
}

static int Player_setname(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	const char* name = lua_tostring(L, 2);
	if (p != NULL)
		p->setname(name);
	return 0;
}

static int Player_getname(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		const char* name = p->getname();
		lua_pushstring(L, name);
		return 1;
	}
	
	return 0;
}

static int Player_setAniKey(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float key = lua_tonumber(L, 2);
		p->setAnimationKey(key);
	}

	return 0;
}

static int Player_getAniKey(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float key = p->getAnimationKey();
		lua_pushnumber(L, key);
		return 1;
	}
	return 0;
}

static int Player_setKeyFrameDur(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float dur = lua_tonumber(L, 2);
		p->setKeyFrameDur(dur);
	}

	return 0;
}

static int Player_getKeyFrameDur(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float dur = p->getKeyFrameDur();
		lua_pushnumber(L, dur);
		return 1;
	}
	return 0;
}

static int Player_setMS(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float ms = lua_tonumber(L, 2);
		p->setMoveSpeed(ms);
	}

	return 0;
}

static int Player_getMS(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float ms = p->getMoveSpeed();
		lua_pushnumber(L, ms);
		return 1;
	}
	return 0;
}

static int Player_setHP(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float hp = lua_tonumber(L, 2);
		p->setHP(hp);
	}

	return 0;
}

static int Player_getHP(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		unsigned int hp = p->getHP();
		lua_pushnumber(L, hp);
		return 1;
	}
	return 0;
}

static int Player_moveSprite(lua_State * L)
{
	Player * p = (Player*)lua_touserdata(L, 1);
	if (p != NULL)
	{
		float x = lua_tonumber(L, 2);
		float y = lua_tonumber(L, 3);
		sf::Vector2f displacement = sf::Vector2f(x, y);
		p->moveSprite(displacement);
	}
	return 0;
}


static void register_player(lua_State * L)
{
	//register the type in Lua with the constructor
	lua_register(L, LUA_PLAYER, Player_new);
	//create a new meta table for this type
	luaL_newmetatable(L, LUA_PLAYER);
	lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
	//push all functions to this meta table and assign the value (name of functions in Lua)
	lua_pushcfunction(L, Player_delete); lua_setfield(L, -2, "__gc");
	lua_pushcfunction(L, Player_setname); lua_setfield(L, -2, LUA_PLAYER_SETNAME);
	lua_pushcfunction(L, Player_getname); lua_setfield(L, -2, LUA_PLAYER_GETNAME);
	lua_pushcfunction(L, Player_setAniKey); lua_setfield(L, -2, LUA_PLAYER_SETANIKEY);
	lua_pushcfunction(L, Player_getAniKey); lua_setfield(L, -2, LUA_PLAYER_GETANIKEY);
	lua_pushcfunction(L, Player_setKeyFrameDur); lua_setfield(L, -2, LUA_PLAYER_SETKEYFRAMEDUR);
	lua_pushcfunction(L, Player_getKeyFrameDur); lua_setfield(L, -2, LUA_PLAYER_GETKEYFRAMEDUR);
	lua_pushcfunction(L, Player_setMS); lua_setfield(L, -2, LUA_PLAYER_SETMS);
	lua_pushcfunction(L, Player_getMS); lua_setfield(L, -2, LUA_PLAYER_GETMS);
	lua_pushcfunction(L, Player_setHP); lua_setfield(L, -2, LUA_PLAYER_SETHP);
	lua_pushcfunction(L, Player_getHP); lua_setfield(L, -2, LUA_PLAYER_GETHP);
	lua_pushcfunction(L, Player_moveSprite); lua_setfield(L, -2, LUA_PLAYER_MOVESPRITE);
	lua_pop(L, 1);
}