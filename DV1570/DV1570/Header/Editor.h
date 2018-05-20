#pragma once
#include "Object.h"
#include "EditorMap.h"
#include <vector>

class Editor : public sf::Drawable
{
private:
	// Spawnpoint (?)
	// Left click add tile
	// Right click remove tile
	EditorMap m_map;

	Object* spawnPointSprite;
	std::vector<Object*> m_saveLoad;
	std::vector<Object*> m_destructibleMapElements;
	std::vector<Object*> m_indestructibleMapElements;

	TileObject m_newTile;

	bool m_buildMode;

	// Editor HUD elements
	std::vector<sf::RectangleShape> m_rectangles;
	sf::RectangleShape m_editorHUD;
	sf::RectangleShape m_pickedObjectHighlight;
	int m_nrOfObjects;

	void _init(sf::RenderWindow &window);

	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

public:
	Editor(sf::RenderWindow &window);
	~Editor();

	void enterBuildMode();
	void exitBuildMode();
	void update(sf::RenderWindow &window);
};