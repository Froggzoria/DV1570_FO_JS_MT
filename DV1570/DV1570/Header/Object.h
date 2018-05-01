#pragma once
#ifndef _OBJECT_H
#define _OBJECT_H
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object();
	Object(std::string pathToTexture, sf::IntRect area = sf::IntRect(), sf::Vector2f position = sf::Vector2f(0, 0));
	~Object();
	sf::Sprite* getSpritePtr();
	void update();
private:
	sf::Vector2f m_pos;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

};
#endif //!_OBJECT_H