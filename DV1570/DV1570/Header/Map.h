#pragma once
#include "Object.h"
#include <vector>

struct TileObject
{
	int type;
	sf::Vector2f pos;
	bool indestructible;
};

class Map : public sf::Drawable
{
private:

protected:
	std::vector<Object*> m_scaledSprites;
	std::vector<TileObject> m_mapTiles;
	std::vector<TileObject> m_indestructibleTiles;
	std::vector<TileObject> m_playerSpawn;
	int m_mapWidth;
	int m_mapHeight;

public:
	Map() { };
	virtual~Map()
	{
		for (int i = 0; i < m_scaledSprites.size(); i++)
		{
			delete m_scaledSprites[i];
			m_scaledSprites[i] = nullptr;
		}
	};

};