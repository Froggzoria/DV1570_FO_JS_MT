extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


#ifndef WEAPON_H
#define WEAPON_H
#include<SFML\Graphics.hpp>
#include<math.h>
using namespace std;

static const float GRAVITY = 9.82f;
static const float PI = 3.14f;
class Weapon
{
private:
	
	sf::Vector2f pos;
	

	float velocity;
	float velocityX;
	float velocityY;
	float massKG;
	float k;

	sf::Vector2f velocityVector;
	sf::Vector2f normalizedVector;



	void normalize();

	string name;
public:
	Weapon();
	~Weapon();

	void shoot(float dt);
	void setValues(const sf::Window &win, sf::Vector2f pos);
	void update(float dt, sf::Vector2f pos, const sf::Window &win);

	void draw(sf::RenderTarget &target, sf::RenderStates &states) const;
};
#endif // !WEAPON_H

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
	sf::CircleShape body; //the projectiles body is just a circle
	sf::Vector2f dir; //initial direction of the projectile
public:
	//the position comes from the weapon/player pos
	Projectile(sf::Vector2f pos, float radius, sf::Vector2f dir) 
	{
		this->body = sf::CircleShape(radius);
		this->body.setFillColor(sf::Color::Red);
		this->body.setPosition(pos);
		this->dir = dir;
	}
	~Projectile(){}
	void Move(sf::Vector2f displacement)
	{
		this->body.move(displacement);
	}
	sf::Vector2f getDir() const { return dir; }
	//it would be the best to let Lua handle the update logic
	//and only have the collision detection on C++
	//if we have collided we stop the Lua script from executing
	void Render(lua_State *L, sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (luaL_dofile(L, "Scripts//Projectile.lua") != EXIT_SUCCESS)
			printf(lua_tostring(L, -1));
		else
		{
			target.draw(this->body, states);
			//resume thread
			lua_getglobal(L, "ResumeUpdate");
			lua_pushlightuserdata(L, (void*)this);
			luaL_setmetatable(L, LUA_PROJECTILE);
			if (lua_pcall(L, 1, 0, 0) != EXIT_SUCCESS)
			{
				printf(lua_tostring(L, -1));
				printf("\n");
			}
		}
		
	}
	
	sf::Vector3f getPosAndRadius() const
	{
		sf::Vector2f pos = this->body.getPosition();
		return sf::Vector3f(pos.x, pos.y, this->body.getRadius());
	}
};
#endif

static int Projectile_new(lua_State* L)
{
	float xPos = lua_tonumber(L, 1);
	float yPos = lua_tonumber(L, 2);
	float radius = lua_tonumber(L, 3);
	float dirX = lua_tonumber(L, 4);
	float dirY = lua_tonumber(L, 5);

	lua_pop(L, 5);

	Projectile* p = new Projectile(sf::Vector2f(xPos, yPos), radius, sf::Vector2f(dirX, dirY));
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

	lua_pushnumber(L, p->getPosAndRadius().x);
	lua_pushnumber(L, p->getPosAndRadius().y);

	return 2;
}

static int Projectile_getradius(lua_State *L)
{
	Projectile *p = (Projectile *)lua_touserdata(L, 1);
	if (p == NULL)
		return 0;
	lua_pushnumber(L, p->getPosAndRadius().z);
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
