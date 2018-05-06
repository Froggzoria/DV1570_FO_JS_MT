#ifndef PLAYER_H
#define PLAYER_H

#include<SFML\Graphics.hpp>
#include<iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

using namespace std;
class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int spriteWidth;
	float speed = 180.0f;
	sf::Vector2f velocity;

	sf::Vector2i currentKeyFrame;
	sf::Vector2i keyFrameSize;
	float animationSpeed;
	float keyFrameDuration;

	lua_State * L;
	const char* name;
	unsigned int hp;
public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	Player(const char* name, unsigned int hp, sf::Vector2f pos);
	~Player();
	void Move();

	void update(float dt);
};
#endif
