#pragma once
#include "Object.h"
#include "Map.h"
#include <vector>

class Editor : public sf::Drawable
{
private:
	Map gameMap;

	std::vector<Object*> m_mapElements;
	std::vector<Object*> m_destructibleMapElements;
	std::vector<Object*> m_indestructibleMapElements;

	bool m_buildMode;

	// Editor HUD elements
	std::vector<sf::RectangleShape> m_rectangles;
	sf::RectangleShape m_editorHUD;
	int m_nrOfObjects;

	void _init(sf::RenderWindow &window);

	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

public:
	Editor(sf::RenderWindow &window);
	~Editor();


	void enterBuildMode();
	void exitBuildMode();
	void update();
};