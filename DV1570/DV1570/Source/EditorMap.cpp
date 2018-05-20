#include "EditorMap.h"
#include <fstream>
#include <iostream>

void EditorMap::_init(int destructibleMapTiles, sf::Vector2i windowDimensions, std::vector<Object*> editorSprites)
{
	m_destructibleMapTiles = destructibleMapTiles;
	m_gridRectangleSize = 40;
	m_mapWidth = windowDimensions.x;
	m_mapHeight = windowDimensions.y;
	int spriteWidth;
	int spriteHeight;
	for (int i = 0; i < editorSprites.size(); i++)
	{
		m_scaledSprites.push_back(new Object(*editorSprites[i]));
		spriteWidth = m_scaledSprites[i]->getSpritePtr()->getLocalBounds().width;
		spriteHeight = m_scaledSprites[i]->getSpritePtr()->getLocalBounds().height;
		m_scaledSprites[i]->getSpritePtr()->setScale(sf::Vector2f((float)m_gridRectangleSize / spriteWidth, (float)m_gridRectangleSize / spriteHeight));
	}
	
	int counter = 0;
	for (int i = 0; i < m_mapHeight; i += 40)
		for (int k = 0; k < m_mapWidth; k += 40)
		{
			m_grid.push_back(sf::RectangleShape());
			m_grid[counter].setSize(sf::Vector2f((float)m_gridRectangleSize, (float)m_gridRectangleSize));
			m_grid[counter].setOutlineThickness(1.0);
			m_grid[counter].setOutlineColor(sf::Color::White);
			m_grid[counter].setFillColor(sf::Color::Transparent);
			float xPos = (float)k;
			float yPos = (float)i;
			m_grid[counter].setPosition(sf::Vector2f(xPos, yPos));
			counter++;
		}
}

void EditorMap::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	for (auto mapTile : m_mapTiles)
	{
		m_scaledSprites[mapTile.type]->getSpritePtr()->setPosition(mapTile.pos);
		window.draw(*m_scaledSprites[mapTile.type]);
	}
	for (auto indesMapTile : m_indestructibleTiles)
	{
		m_scaledSprites[indesMapTile.type]->getSpritePtr()->setPosition(indesMapTile.pos);
		window.draw(*m_scaledSprites[indesMapTile.type]);
	}
	for (auto spawn : m_playerSpawn)
	{
		m_scaledSprites[spawn.type]->getSpritePtr()->setPosition(spawn.pos);
		window.draw(*m_scaledSprites[spawn.type]);
	}
	for (auto grid : m_grid)
		window.draw(grid);
}

EditorMap::EditorMap()
{
}

EditorMap::~EditorMap()
{
}

void EditorMap::initiateEditorMap(int destructibleMapTiles, sf::Vector2i windowDimensions, std::vector<Object*> editorSprites)
{
	_init(destructibleMapTiles, windowDimensions, editorSprites);
}

int EditorMap::getGridRectangleSize() const
{
	return m_gridRectangleSize;
}

void EditorMap::placeMapTile(TileObject newTile)
{
	sf::Vector2f newTileCornerPos;
	int newTilePosX = (int)newTile.pos.x - ((int)newTile.pos.x % m_gridRectangleSize);
	int newTilePosY = (int)newTile.pos.y - ((int)newTile.pos.y % m_gridRectangleSize);
	newTileCornerPos = sf::Vector2f((float)newTilePosX, (float)newTilePosY);
	bool alreadyPlaced = false;

	for (auto spawn : m_playerSpawn)
	{
		if (spawn.pos == newTileCornerPos)
		{
			alreadyPlaced = true;
			break;
		}
	}
	if (newTile.type < m_destructibleMapTiles)
	{
		for (auto mapTile : m_mapTiles)
		{
			if (mapTile.pos == newTileCornerPos)
			{
				alreadyPlaced = true;
				break;
			}
		}
	}
	else
	{
		for (auto indesMapTile : m_indestructibleTiles)
		{
			if (indesMapTile.pos == newTileCornerPos)
			{
				alreadyPlaced = true;
				break;
			}
		}
	}
	if (!alreadyPlaced)
	{
		newTile.pos = newTileCornerPos;
		if (newTile.type < m_destructibleMapTiles)
		{
			m_mapTiles.push_back(newTile);
		}
		else
		{
			m_indestructibleTiles.push_back(newTile);
		}
	}
}

void EditorMap::removeMapTile(sf::Vector2i mousePos)
{
	int rectangleMousePosX = mousePos.x - (mousePos.x % m_gridRectangleSize);
	int rectangleMousePosY = mousePos.y - (mousePos.y % m_gridRectangleSize);
	sf::Vector2f rectCornerPos = sf::Vector2f((float)rectangleMousePosX, (float)rectangleMousePosY);
	int counter = 0;

	for (auto mapTile : m_mapTiles)
	{
		if (rectCornerPos == mapTile.pos)
		{
			m_mapTiles.erase(m_mapTiles.begin() + counter);
			break;
		}
		counter++;
	}
	counter = 0;
	for (auto indesMapTile : m_indestructibleTiles)
	{
		if (rectCornerPos == indesMapTile.pos)
		{
			m_indestructibleTiles.erase(m_indestructibleTiles.begin() + counter);
			break;
		}
		counter++;
	}
	counter = 0;
	for (auto spawn : m_playerSpawn)
	{
		if (rectCornerPos == spawn.pos)
		{
			m_playerSpawn.erase(m_playerSpawn.begin() + counter);
			break;
		}
		counter++;
	}
}

void EditorMap::setPlayerSpawn(TileObject spawn)
{
	sf::Vector2f newTileCornerPos;
	int newTilePosX = (int)spawn.pos.x - ((int)spawn.pos.x % m_gridRectangleSize);
	int newTilePosY = (int)spawn.pos.y - ((int)spawn.pos.y % m_gridRectangleSize);
	newTileCornerPos = sf::Vector2f((float)newTilePosX, (float)newTilePosY);
	bool alreadyPlaced = false;

	for (auto mapTile : m_mapTiles)
	{
		if (mapTile.pos == newTileCornerPos)
		{
			alreadyPlaced = true;
			break;
		}
	}
	for (auto indesMapTile : m_indestructibleTiles)
	{
		if (indesMapTile.pos == newTileCornerPos)
		{
			alreadyPlaced = true;
			break;
		}
	}
	for (auto spawn : m_playerSpawn)
	{
		if (spawn.pos == newTileCornerPos)
		{
			alreadyPlaced = true;
			break;
		}
	}
	if (!alreadyPlaced)
	{
		spawn.pos = newTileCornerPos;
		m_playerSpawn.push_back(spawn);
	}

}

void EditorMap::saveMap(std::string path)
{
	std::ofstream save;
	save.open(path);

	if (save.is_open())
	{
		// Destructible objects
		for (auto tiles : m_mapTiles)
		{
			save << tiles.type << std::endl;
			save << tiles.pos.x << std::endl;
			save << tiles.pos.y << std::endl;
			save << tiles.indestructible << std::endl;
		}
		// Indestructible objects
		save << -1 << std::endl;
		for (auto tiles : m_indestructibleTiles)
		{
			save << tiles.type << std::endl;
			save << tiles.pos.x << std::endl;
			save << tiles.pos.y << std::endl;
			save << tiles.indestructible << std::endl;
		}
		save << -1 << std::endl;
		for (auto spawn : m_playerSpawn)
		{
			save << spawn.type << std::endl;
			save << spawn.pos.x << std::endl;
			save << spawn.pos.y << std::endl;
			save << spawn.indestructible << std::endl;
		}
		// Remaining variables
		save << -1 << std::endl;
		save << m_mapWidth << std::endl;
		save << m_mapHeight << std::endl;
		save << "EOF" << std::endl;
		save.close();
	}
}

void EditorMap::loadMap(std::string path)
{
	std::ifstream load;
	load.open(path);

	if (load.is_open())
	{
		// Clear old data
		m_mapTiles.clear();
		m_indestructibleTiles.clear();
		m_playerSpawn.clear();

		// Read the whole file in one sequence
		std::vector<std::string> data;
		std::string next;
		bool eof = false;

		while (!eof)
		{
			std::getline(load, next);
			if (next == "EOF")
				eof = true;
			else
				data.push_back(next);
		}

		//std::cout.write(data, length);
		int arrayIndex = 0;
		std::vector<int> dataInt;
		TileObject recreateData;

		for (int i = 0; i < data.size(); i++)
		{
			dataInt.push_back(std::stoi(data[i]));
		}
		for (int i = 0; i < dataInt.size(); i += 4)
		{
			if (-1 != dataInt[i])
			{
				if (3 != arrayIndex)
				{
					recreateData.type = dataInt[i];
					recreateData.pos = sf::Vector2f((float)dataInt[i + 1], (float)dataInt[i + 2]);
					recreateData.indestructible = dataInt[i + 3];
					if (0 == arrayIndex)
						m_mapTiles.push_back(recreateData);
					else if (1 == arrayIndex)
						m_indestructibleTiles.push_back(recreateData);
					else
						m_playerSpawn.push_back(recreateData);
				}
				else
				{
					m_mapWidth = dataInt[i];
					m_mapHeight = dataInt[i + 1];
				}
			}
			else
			{
				arrayIndex++;
				i -= 3;
			}
		}
	}
}

void EditorMap::saveLUA(std::string path)
{
	std::ofstream save;
	save.open(path);

	if (save.is_open())
	{
		// Destructible objects
		save << "Player Max 100 200 400" << std::endl;
		//save << "Player Frogge 100 200 400" << std::endl;
		for (auto tiles : m_mapTiles)
		{
			save << "GameTile" << " ";
			save << "Sand" << " ";
			save << tiles.pos.x << " ";
			save << tiles.pos.y << std::endl;
		}
		// Indestructible objects
		for (auto tiles : m_indestructibleTiles)
		{
			save << "GameTile" << " ";
			save << "Boulder" << " ";
			save << tiles.pos.x << " ";
			save << tiles.pos.y << std::endl;
		}
		for (auto spawn : m_playerSpawn)
		{
			save << "Spawn" << " ";
			save << spawn.pos.x << " ";
			save << spawn.pos.y << std::endl;
		}
		// Remaining variables
		save << "UTILITY" << std::endl;
		save << m_mapWidth << std::endl;
		save << m_mapHeight << std::endl;
		save << "EOF" << std::endl;
		save.close();
	}
}

void EditorMap::update(sf::RenderWindow &window)
{

}