#include "Editor.h"
#include <iostream>

void Editor::_init(sf::RenderWindow &window)
{
	std::vector<Object*> mapObjects;
	// Initialize the different map tiles and objects
	// Destructible objects
	m_destructibleMapElements.push_back(new Object("../Assets/platformerGraphicsDeluxe_Updated/Tiles/grassCenter.png"));
	for (auto obj : m_destructibleMapElements)
		mapObjects.push_back(obj);
	// Indestructible objects
	m_indestructibleMapElements.push_back(new Object("../Assets/platformerGraphicsDeluxe_Updated/Items/rock.png"));
	for (auto obj : m_indestructibleMapElements)
		mapObjects.push_back(obj);

	for (int i = 1; i < m_destructibleMapElements.size(); i++)
		m_destructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(0.0f, (m_destructibleMapElements.at(i - 1)->getSpritePtr()->getPosition().y + m_destructibleMapElements.at(i - 1)->getSpritePtr()->getTextureRect().height + 1)));
	m_indestructibleMapElements.at(0)->getSpritePtr()->setPosition(sf::Vector2f(0.0f, (m_destructibleMapElements.at(m_destructibleMapElements.size() - 1)->getSpritePtr()->getPosition().y + m_destructibleMapElements.at(m_destructibleMapElements.size() - 1)->getSpritePtr()->getTextureRect().height + m_destructibleMapElements.at(m_destructibleMapElements.size() - 1)->getSpritePtr()->getTextureRect().height * 0.5 + 1)));
	for (int i = 1; i < m_indestructibleMapElements.size(); i++)
		m_indestructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(0.0f, (m_indestructibleMapElements.at(i - 1)->getSpritePtr()->getPosition().y + m_indestructibleMapElements.at(i - 1)->getSpritePtr()->getTextureRect().height + 1)));

	m_nrOfObjects = m_indestructibleMapElements.size() + m_destructibleMapElements.size() + 1;

	// Create the editor HUD
	float spriteWidth;
	float spriteHeight;
	float windowWidth = window.getSize().x;
	float windowHeight = window.getSize().y;
	float HUDHeight = windowHeight * 0.2f;
	int outlineThickness = 2.0f;
	float rectangleSize = (windowHeight * 0.1f - outlineThickness);

	m_editorHUD.setSize(sf::Vector2f(windowWidth, HUDHeight));
	m_editorHUD.setPosition(sf::Vector2f(0.0f, windowHeight - m_editorHUD.getSize().y));
	m_editorHUD.setOutlineThickness(outlineThickness);
	m_editorHUD.setOutlineColor(sf::Color::Green);
	m_editorHUD.setFillColor(sf::Color::Transparent);
	m_buildMode = false;

	m_pickedObjectHighlight.setSize(sf::Vector2f(rectangleSize, rectangleSize));
	m_pickedObjectHighlight.setOutlineThickness(outlineThickness);
	m_pickedObjectHighlight.setOutlineColor(sf::Color::Transparent);
	m_pickedObjectHighlight.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < m_nrOfObjects - 1; i++)
	{
		m_rectangles.push_back(sf::RectangleShape(sf::Vector2f(rectangleSize, rectangleSize)));
		m_rectangles.at(i).setOutlineThickness(outlineThickness);
		m_rectangles.at(i).setOutlineColor(sf::Color::Red);
		m_rectangles.at(i).setFillColor(sf::Color::Transparent);
		m_rectangles.at(i).setPosition(sf::Vector2f(outlineThickness, windowHeight - (rectangleSize * (i + 1) + outlineThickness)));
		std::cout << windowHeight - (rectangleSize * (i + 1) + outlineThickness) << std::endl;
	}

	for (int i = 0; i < m_destructibleMapElements.size(); i++)
	{
		spriteWidth = m_destructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().width;
		spriteHeight = m_destructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().height;
		m_destructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(m_rectangles.at(i).getPosition().x, m_rectangles.at(i).getPosition().y));
		m_destructibleMapElements.at(i)->getSpritePtr()->setScale(sf::Vector2f(rectangleSize / spriteWidth, rectangleSize / spriteHeight));
	}
	for (int i = 0; i < m_indestructibleMapElements.size(); i++)
	{
		spriteWidth = m_indestructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().width;
		spriteHeight = m_indestructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().height;
		m_indestructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(m_rectangles.at(i + m_destructibleMapElements.size()).getPosition().x, m_rectangles.at(i + m_destructibleMapElements.size()).getPosition().y - outlineThickness));
		m_indestructibleMapElements.at(i)->getSpritePtr()->setScale(sf::Vector2f(rectangleSize / spriteWidth, rectangleSize / spriteHeight));
	}

	m_rectangles.push_back(sf::RectangleShape(sf::Vector2f(rectangleSize, rectangleSize)));
	m_rectangles[m_nrOfObjects - 1].setOutlineThickness(outlineThickness);
	m_rectangles[m_nrOfObjects - 1].setOutlineColor(sf::Color::Red);
	m_rectangles[m_nrOfObjects - 1].setFillColor(sf::Color::Transparent);
	m_rectangles[m_nrOfObjects - 1].setPosition(sf::Vector2f(outlineThickness + rectangleSize, windowHeight - rectangleSize - outlineThickness));
	spawnPointSprite = new Object("../Assets/platformerGraphicsDeluxe_Updated/Player/p1_front.png");
	spriteWidth = spawnPointSprite->getSpritePtr()->getLocalBounds().width;
	spriteHeight = spawnPointSprite->getSpritePtr()->getLocalBounds().height;
	spawnPointSprite->getSpritePtr()->setPosition(sf::Vector2f(m_rectangles[m_nrOfObjects - 1].getPosition().x, m_rectangles[m_nrOfObjects - 1].getPosition().y));
	spawnPointSprite->getSpritePtr()->setScale(sf::Vector2f(rectangleSize / spriteWidth, rectangleSize / spriteHeight));
	mapObjects.push_back(spawnPointSprite);

	m_saveLoad.push_back(new Object("../Assets/platformerGraphicsDeluxe_Updated/SaveLoad/Save.png"));
	m_saveLoad.push_back(new Object("../Assets/platformerGraphicsDeluxe_Updated/SaveLoad/Load.png"));

	int rectVecSize = m_rectangles.size();

	for (int i = 0; i < m_saveLoad.size(); i++)
	{
		spriteWidth = m_saveLoad[i]->getSpritePtr()->getLocalBounds().width;
		spriteHeight = m_saveLoad[i]->getSpritePtr()->getLocalBounds().height;
		m_rectangles.push_back(sf::RectangleShape(sf::Vector2f(rectangleSize, rectangleSize)));
		m_rectangles[rectVecSize + i].setOutlineThickness(outlineThickness);
		m_rectangles[rectVecSize + i].setOutlineColor(sf::Color::Red);
		m_rectangles[rectVecSize + i].setFillColor(sf::Color::Transparent);
		m_rectangles[rectVecSize + i].setPosition(sf::Vector2f((outlineThickness * 2) + (rectangleSize * 2), windowHeight - ((rectangleSize * (i + 1)) + (outlineThickness * (i + 1)))));
		m_saveLoad[i]->getSpritePtr()->setPosition(sf::Vector2f(m_rectangles[rectVecSize + i].getPosition().x, m_rectangles[rectVecSize + i].getPosition().y));
		m_saveLoad[i]->getSpritePtr()->setScale(sf::Vector2f(rectangleSize / spriteWidth, rectangleSize / spriteHeight));
		std::cout << windowHeight - (rectangleSize * (i + 1) + outlineThickness) << std::endl;
	}

	sf::Vector2u windowSize = window.getSize();
	m_map.initiateEditorMap(m_destructibleMapElements.size(), sf::Vector2i((int)windowSize.x, (int)windowSize.y - HUDHeight), mapObjects);
}

void Editor::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	// Draw the remainder of the HUD
	for (int i = 0; i < m_saveLoad.size(); i++)
		window.draw(*m_saveLoad[i]);
	for (int i = 0; i < m_rectangles.size(); i++)
	{
		window.draw(m_rectangles.at(i));
	}
	for (int i = 0; i < m_destructibleMapElements.size(); i++)
		window.draw(*m_destructibleMapElements.at(i));
	for (int i = 0; i < m_indestructibleMapElements.size(); i++)
		window.draw(*m_indestructibleMapElements.at(i));
	window.draw(*spawnPointSprite);
	window.draw(m_map);
	window.draw(m_pickedObjectHighlight);
	window.draw(m_editorHUD);
}

Editor::Editor(sf::RenderWindow &window)
{
	_init(window);
}

Editor::~Editor()
{
	for (int i = 0; i < m_destructibleMapElements.size(); i++)
	{
		delete m_destructibleMapElements.at(i);
		m_destructibleMapElements.at(i) = nullptr;
	}
	for (int i = 0; i < m_indestructibleMapElements.size(); i++)
	{
		delete m_indestructibleMapElements.at(i);
		m_indestructibleMapElements.at(i) = nullptr;
	}
	for (int i = 0; i < m_saveLoad.size(); i++)
	{
		delete m_saveLoad[i];
		m_saveLoad[i] = nullptr;
	}
	delete spawnPointSprite;
}

void Editor::enterBuildMode()
{
	m_buildMode = true;
}

void Editor::exitBuildMode()
{
	m_buildMode = false;
	// Open file stream to save the map

}

void Editor::update(sf::RenderWindow &window)
{
	static bool keyPressedEditor = false;
	static bool isPicked = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !keyPressedEditor)
	{
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);

		if (isPicked && mouseCoords.y < m_editorHUD.getPosition().y && m_newTile.type != m_destructibleMapElements.size() + m_indestructibleMapElements.size())
		{
			m_newTile.pos = sf::Vector2f((float)mouseCoords.x, (float)mouseCoords.y);
			m_map.placeMapTile(m_newTile);
		}
		else if (isPicked && mouseCoords.y < m_editorHUD.getPosition().y && m_newTile.type == m_destructibleMapElements.size() + m_indestructibleMapElements.size())
		{
			m_newTile.pos = sf::Vector2f((float)mouseCoords.x, (float)mouseCoords.y);
			m_map.setPlayerSpawn(m_newTile);
		}
		else
		{
			bool indestructible = false;
			float rectangleSize = (window.getSize().y * 0.1f);
			int xCoord = mouseCoords.x - (mouseCoords.x % (int)rectangleSize); // to only check against corners of rectangles
			int yCoord = mouseCoords.y - (mouseCoords.y % (int)rectangleSize); // to only check against corners of rectangles
			int outlineThickness = m_rectangles[0].getOutlineThickness();
			int posX;
			int posY;
			
			for (int i = 0; i < m_destructibleMapElements.size(); i++)
			{
				posX = (m_destructibleMapElements[i]->getSpritePtr()->getPosition().x - outlineThickness);
				posY = m_destructibleMapElements[i]->getSpritePtr()->getPosition().y;

				if (xCoord == posX && yCoord == posY)
				{
					m_newTile.type = i;
					m_newTile.indestructible = false;
					isPicked = true;
				}
			}
			for (int i = 0; i < m_indestructibleMapElements.size(); i++)
			{
				posX = (m_indestructibleMapElements[i]->getSpritePtr()->getPosition().x - outlineThickness);
				posY = m_indestructibleMapElements[i]->getSpritePtr()->getPosition().y;

				if (xCoord == posX && yCoord == posY)
				{
					m_newTile.type = i + m_destructibleMapElements.size();
					m_newTile.indestructible = true;
					isPicked = true;
				}
			}
			for (int i = 0; i < m_saveLoad.size(); i++)
			{
				posX = m_saveLoad[i]->getSpritePtr()->getPosition().x;
				posY = m_saveLoad[i]->getSpritePtr()->getPosition().y;

				if (xCoord == posX && yCoord == posY)
				{
					if (0 == i)
					{
						std::string path;
						std::cout << "Save file as:" << std::endl;
						std::cin >> path;
						path = "Levels/" + path;
						path += ".fmj";

						m_map.saveMap(path);
					}
					else
					{
						std::string path;
						std::cout << "Load file:" << std::endl;
						std::cin >> path;
						path = "Levels/" + path;
						path += ".fmj";
						m_map.loadMap(path);
					}
				}
			}
			posX = spawnPointSprite->getSpritePtr()->getPosition().x;
			posY = spawnPointSprite->getSpritePtr()->getPosition().y;
			if (xCoord == posX && yCoord == posY)
			{
				m_newTile.type = m_destructibleMapElements.size() + m_indestructibleMapElements.size();
				m_newTile.indestructible = true;
				isPicked = true;
			}
			if (isPicked)
			{
				if (m_newTile.type == m_destructibleMapElements.size() + m_indestructibleMapElements.size())
					m_pickedObjectHighlight.setPosition(spawnPointSprite->getSpritePtr()->getPosition());
				else if (!m_newTile.indestructible)
					m_pickedObjectHighlight.setPosition(m_destructibleMapElements[m_newTile.type]->getSpritePtr()->getPosition());
				else
					m_pickedObjectHighlight.setPosition(m_indestructibleMapElements[m_newTile.type - m_destructibleMapElements.size()]->getSpritePtr()->getPosition());
				m_pickedObjectHighlight.setOutlineColor(sf::Color::Yellow);
			}
		}
		keyPressedEditor = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !keyPressedEditor)
	{
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);

		if (mouseCoords.y < m_editorHUD.getPosition().y)
		{
			m_map.removeMapTile(mouseCoords);
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && keyPressedEditor)
		keyPressedEditor = false;

	m_map.update(window);
}