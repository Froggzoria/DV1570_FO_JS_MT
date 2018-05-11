#include "Player.h"

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Player::Player(const char* name, unsigned int hp, sf::Vector2f pos)
{
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

	// Initialize animation variables.
	currentKeyFrame = sf::Vector2i(0, 0);
	keyFrameSize = sf::Vector2i(32, 32);
	spriteWidth = 4;
	animationSpeed = 0.2f;
	keyFrameDuration = 0.0f;
	sprite.setPosition(pos);
}

Player::~Player()
{

}

void Player::update(float dt, lua_State * L)
{
	this->Move(dt, L);

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

void Player::Move(float dt, lua_State * L)
{
	lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	lua_setglobal(L, "MOVE_LEFT");
	lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
	lua_setglobal(L, "MOVE_RIGHT");
	lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
	lua_setglobal(L, "MOVE_UP");
	lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
	lua_setglobal(L, "MOVE_DOWN");

	lua_getglobal(L, "MovePlayer");
	lua_pushnumber(L, this->speed);
	lua_pushnumber(L, dt);
	lua_pushnumber(L, keyFrameDuration);

	if (lua_pcall(L, 3, 4, 0) == EXIT_SUCCESS)
	{
		keyFrameDuration = lua_tonumber(L, -1);
		currentKeyFrame.y = lua_tonumber(L, -2);
		sprite.move(sf::Vector2f(lua_tonumber(L, -4), lua_tonumber(L, -3)));
		lua_pop(L, 4);
	}
}