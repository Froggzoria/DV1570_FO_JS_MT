#pragma once
#include "Map.h"

class EditorMap : public Map
{
private:
	std::vector<sf::RectangleShape> m_grid;
	int m_gridRectangleSize;
	int m_destructibleMapTiles;

	virtual void _init(int destructibleMapTiles, sf::Vector2i windowDimensions, std::vector<Object*> editorSprites);
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

public:
	EditorMap();
	virtual ~EditorMap();

	void initiateEditorMap(int destructibleMapTiles, sf::Vector2i windowDimensions, std::vector<Object*> editorSprites);

	int getGridRectangleSize() const;

	void placeMapTile(TileObject newTile);
	void removeMapTile(sf::Vector2i mousePos);
	void setPlayerSpawn(TileObject spawn);

	void saveMap(std::string path);
	void loadMap(std::string path);

	void saveLUA(std::string path);

	virtual void update(sf::RenderWindow &window);
};