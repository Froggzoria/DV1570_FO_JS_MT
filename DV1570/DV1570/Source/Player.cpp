#include "Player.h"

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	wep.draw(target, states);
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

void Player::update(float dt, lua_State * L, const sf::Window &win)
{
	this->Move(L);

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
	this->wep.update(dt, sprite.getPosition(), win);
}

void Player::Move(lua_State * L)
{
	//only run the script on input
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
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
		lua_pushlightuserdata(L, (void*)this);
		if (lua_pcall(L, 1, 0, 0) != EXIT_SUCCESS)
		{
			printf(lua_tostring(L, -1));
		}
	}
}