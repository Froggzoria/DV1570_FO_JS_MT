#pragma once
#ifndef GAME_TILE_H
#define GAME_TILE_H

#include "SFML/Graphics.hpp"
#include <string>

#define SAND_TYPE "Sand"
#define BOULDER_TYPE "Boulder"

#define SAND_TYPE_PATH "../Assets/platformerGraphicsDeluxe_Updated/Tiles/grassCenter.png"
#define BOULDER_TYPE_PATH "../Assets/platformerGraphicsDeluxe_Updated/Items/rock.png"

class GameTile : public sf::Drawable
{
public:
	GameTile(std::string type, int posX, int posY);
	~GameTile(){}

	sf::Sprite getSprite() { return m_sprite; }
	sf::FloatRect getBounds() { return m_sprite.getLocalBounds(); }
	void onProjectileEvent(sf::Vector2f impactPoint, float blastRadius);

	void draw(sf::RenderTarget &window, sf::RenderStates states) const;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	bool isDestructable;
};

#endif