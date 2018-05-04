#include "Player.h"

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Player::Player(sf::Vector2f pos)
{
	sf::String fileName = "../Resources/player1.png";
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

}

void Player::update(float dt)
{
	//Keyboard inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -1.0f;
		keyFrameDuration += dt;
		currentKeyFrame.y = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = 1.0f;
		keyFrameDuration += dt;
		currentKeyFrame.y = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y = 1.0f;
		keyFrameDuration += dt;
		currentKeyFrame.y = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -1.0f;
		keyFrameDuration += dt;
		currentKeyFrame.y = 4;
	}
	else
	{
		velocity.x = 0.0f;
	}
	if (velocity.y > 2)
	{
		velocity.y = 0.0f;
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
