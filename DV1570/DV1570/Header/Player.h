#ifndef PLAYER_H
#define PLAYER_H

#include<SFML\Graphics.hpp>
#include<iostream>
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

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Player(sf::Vector2f pos);
	~Player();

	void update(float dt);
};
#endif
