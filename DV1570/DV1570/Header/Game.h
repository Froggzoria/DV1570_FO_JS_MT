#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML\Graphics.hpp>
#include"Player.h"

class Game : public sf::Drawable
{
private:
	sf::Texture backgroundTex;
	sf::Sprite backgroundSprite;
	Player player;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Game();

	void Update(float dt, const sf::Window &win);
};
#endif