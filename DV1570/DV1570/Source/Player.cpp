#include "Player.h"

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Player::Player(const char* name, unsigned int hp, sf::Vector2f pos)
{
	this->L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "Scripts//Player.lua");

	this->name = name;
	this->hp = hp;
	sf::String fileName = "..//Resources//player1.png";
	if (!texture.loadFromFile(fileName))
	{
		// Handle error: Print error message.
		std::cout << "ERROR: Player image could not be loaded.\n---" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	// Initialise animation variables.
	currentKeyFrame = sf::Vector2i(0, 0);
	keyFrameSize = sf::Vector2i(32, 32);
	spriteWidth = 4;
	animationSpeed = 0.2f;
	keyFrameDuration = 0.0f;
	sprite.setPosition(pos);
	velocity = (sf::Vector2f(0.0f, 0.0f));
}

Player::~Player()
{
	lua_close(L);
}

void Player::update(float dt)
{
	//Keyboard inputs
	velocity.x = 0.0f;
	velocity.y = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		lua_getglobal(L, "Move");
		lua_pushnumber(L, sf::Keyboard::Left);
		if (lua_pcall(L, 1, 1, 0) == EXIT_SUCCESS)
			velocity.x = lua_tonumber(L, -1);
		keyFrameDuration += dt;
		currentKeyFrame.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		lua_getglobal(L, "Move");
		lua_pushnumber(L, sf::Keyboard::Right);
		if (lua_pcall(L, 1, 1, 0) == EXIT_SUCCESS)
			velocity.x = lua_tonumber(L, -1);
		keyFrameDuration += dt;
		currentKeyFrame.y = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		lua_getglobal(L, "Move");
		lua_pushnumber(L, sf::Keyboard::Down);
		if (lua_pcall(L, 1, 1, 0) == EXIT_SUCCESS)
			velocity.y = lua_tonumber(L, -1);
		keyFrameDuration += dt;
		currentKeyFrame.y = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		lua_getglobal(L, "Move");
		lua_pushnumber(L, sf::Keyboard::Up);
		if (lua_pcall(L, 1, 1, 0) == EXIT_SUCCESS)
			velocity.y = lua_tonumber(L, -1);
		keyFrameDuration += dt;
		currentKeyFrame.y = 3;
	}
	//actual movement
	sprite.move(velocity * speed * dt);

	

	//Update animation
	if (keyFrameDuration >= animationSpeed)
	{
		currentKeyFrame.x++;

		if (currentKeyFrame.x >= spriteWidth)
			currentKeyFrame.x = 0;

		sprite.setTextureRect(sf::IntRect(currentKeyFrame.x * keyFrameSize.x,
			currentKeyFrame.y * keyFrameSize.y, keyFrameSize.x, keyFrameSize.y));
		keyFrameDuration = 0.0f;
	}

}

void Player::Move()
{

}