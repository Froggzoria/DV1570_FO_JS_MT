extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include<SFML\Graphics.hpp>
#include<math.h>
#ifndef PROJECTILE_H
#define PROJECTILE_H

//lets define a uniform projectile speed 
#define PROJECTILE_SPEED_CONSTANT 125.0f
#define MIN_SPEED_MULTIPLIER 1.0
#define MAX_SPEED_MULTIPLIER 3.0

//define LUa properties for this class
#define LUA_PROJECTILE "Projectile"
#define LUA_PROJECTILE_MOVE "Move"
#define LUA_PROJECTILE_GETDIR "GetDir"
#define LUA_PROJECTILE_GETPOS "GetPos"
#define LUA_PROJECTILE_GETRADIUS "GetRadius"

class Projectile
{
private:
	sf::Sprite* body; //the projectiles body is just a circle
	sf::Vector2f dir; //initial direction of the projectile
	sf::Vector2f posPlaceHolder;
public:
	//the position comes from the weapon/player pos
	Projectile(sf::Vector2f pos, sf::Vector2f dir)
	{
		this->posPlaceHolder = pos;
		this->dir = dir;
	}
	~Projectile() {}
	void Move(sf::Vector2f displacement)
	{
		this->body->move(displacement);
	}
	sf::Vector2f getDir() const { return dir; }
	//it would be the best to let Lua handle the update logic
	//and only have the collision detection on C++
	//if we have collided we stop the Lua script from executing
	void Render(lua_State *L, sf::RenderTarget & target, sf::RenderStates states) const;
	void setSpritePtr(sf::Sprite*ptr) { body = ptr; }
	sf::Vector3f getCenterPosAndRadius() const;
};
#endif

#ifndef WEAPON_H
#define WEAPON_H

using namespace std;

class Weapon
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	Projectile * currentProjectile;
public:
	bool hasProjectile = false;
	Weapon();
	~Weapon();
	void Update(lua_State *L);
	void setNewProjectilePtr(Projectile * p, sf::Vector2f pos) { 
		hasProjectile = true;
		currentProjectile = p;
		m_sprite.setPosition(pos);
		currentProjectile->setSpritePtr(&m_sprite);
	}
	void draw(lua_State *L, sf::RenderTarget & target, sf::RenderStates states) const;
};
#endif // !WEAPON_H



static int Projectile_new(lua_State* L)
{
	float xPos = lua_tonumber(L, 1);
	float yPos = lua_tonumber(L, 2);
	float dirX = lua_tonumber(L, 3);
	float dirY = lua_tonumber(L, 4);

	lua_pop(L, 4);

	Projectile* p = new Projectile(sf::Vector2f(xPos, yPos), sf::Vector2f(dirX, dirY));
	lua_pushlightuserdata(L, (void*)p);
	luaL_setmetatable(L, LUA_PROJECTILE);

	return 1;
}

static int Projectile_delete(lua_State *L)
{
	delete (Projectile*)lua_touserdata(L, 1);
	return 0;
}

static int Projectile_move(lua_State* L)
{
	Projectile *p = (Projectile *)lua_touserdata(L, 1);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	lua_pop(L, 3);

	p->Move(sf::Vector2f(x, y));
	return 0;
}

static int Projectile_getdir(lua_State* L)
{
	Projectile *p = (Projectile *)lua_touserdata(L, 1);
	if (p == NULL)
		return 0;

	sf::Vector2f dir = p->getDir();
	lua_pushnumber(L, dir.x);
	lua_pushnumber(L, dir.y);

	return 2;
}

static int Projectile_getpos(lua_State* L)
{
	Projectile *p = (Projectile *)lua_touserdata(L, 1);
	if (p == NULL)
		return 0;

	lua_pushnumber(L, p->getCenterPosAndRadius().x);
	lua_pushnumber(L, p->getCenterPosAndRadius().y);

	return 2;
}

static int Projectile_getradius(lua_State *L)
{
	Projectile *p = (Projectile *)lua_touserdata(L, 1);
	if (p == NULL)
		return 0;
	lua_pushnumber(L, p->getCenterPosAndRadius().z);
	return 1;
}

static void register_projectile(lua_State *L)
{
	//set a uniform speed  for projectiles
	lua_pushnumber(L, PROJECTILE_SPEED_CONSTANT);
	lua_setglobal(L, "PROJECTILE_SPEED");

	lua_register(L, LUA_PROJECTILE, Projectile_new);
	luaL_newmetatable(L, LUA_PROJECTILE);
	lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, Projectile_delete); lua_setfield(L, -2, "__gc");
	lua_pushcfunction(L, Projectile_move); lua_setfield(L, -2, LUA_PROJECTILE_MOVE);
	lua_pushcfunction(L, Projectile_getdir); lua_setfield(L, -2, LUA_PROJECTILE_GETDIR);
	lua_pushcfunction(L, Projectile_getpos); lua_setfield(L, -2, LUA_PROJECTILE_GETPOS);
	lua_pushcfunction(L, Projectile_getradius); lua_setfield(L, -2, LUA_PROJECTILE_GETRADIUS);

	lua_pop(L, 1);
}
