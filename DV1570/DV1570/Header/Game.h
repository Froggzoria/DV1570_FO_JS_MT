#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML\Graphics.hpp>
#include"Player.h"

class Game : public sf::Drawable
{
private:
	sf::Texture mBackgroundTex;
	sf::Sprite mBackgroundSprite;
	Player player;

	//Tiles tiles;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
public:
	Game();

	void Update(float dt);
};
#endif