#include "Editor.h"
#include <iostream>

void Editor::_init(sf::RenderWindow &window)
{
	// Initialize the different map tiles and objects
	// Destructible objects
	m_destructibleMapElements.push_back(new Object("D:/Liero/DV1570_FO_JS_MT/DV1570/Assets/platformerGraphicsDeluxe_Updated/Tiles/grassCenter.png"));

	// Indestructible objects
	m_indestructibleMapElements.push_back(new Object("D:/Liero/DV1570_FO_JS_MT/DV1570/Assets/platformerGraphicsDeluxe_Updated/Items/rock.png"));
	//m_indestructibleMapElements.push_back(new Object("D:/Liero/DV1570_FO_JS_MT/DV1570/Assets/platformerGraphicsDeluxe_Updated/Tiles/castleHalf.png"));
	//m_indestructibleMapElements.push_back(new Object("D:/Liero/DV1570_FO_JS_MT/DV1570/Assets/platformerGraphicsDeluxe_Updated/Tiles/castleHalfLeft.png"));
	//m_indestructibleMapElements.push_back(new Object("D:/Liero/DV1570_FO_JS_MT/DV1570/Assets/platformerGraphicsDeluxe_Updated/Tiles/castleHalfMid.png"));
	//m_indestructibleMapElements.push_back(new Object("D:/Liero/DV1570_FO_JS_MT/DV1570/Assets/platformerGraphicsDeluxe_Updated/Tiles/castleHalfRight.png"));

	for (int i = 1; i < m_destructibleMapElements.size(); i++)
		m_destructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(0.0f, (m_destructibleMapElements.at(i - 1)->getSpritePtr()->getPosition().y + m_destructibleMapElements.at(i - 1)->getSpritePtr()->getTextureRect().height + 1)));
	m_indestructibleMapElements.at(0)->getSpritePtr()->setPosition(sf::Vector2f(0.0f, (m_destructibleMapElements.at(m_destructibleMapElements.size() - 1)->getSpritePtr()->getPosition().y + m_destructibleMapElements.at(m_destructibleMapElements.size() - 1)->getSpritePtr()->getTextureRect().height + m_destructibleMapElements.at(m_destructibleMapElements.size() - 1)->getSpritePtr()->getTextureRect().height * 0.5 + 1)));
	for (int i = 1; i < m_indestructibleMapElements.size(); i++)
		m_indestructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(0.0f, (m_indestructibleMapElements.at(i - 1)->getSpritePtr()->getPosition().y + m_indestructibleMapElements.at(i - 1)->getSpritePtr()->getTextureRect().height + 1)));
	
	m_nrOfObjects = m_indestructibleMapElements.size() + m_destructibleMapElements.size();

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

	for (int i = 0; i < m_nrOfObjects; i++)
	{
		m_rectangles.push_back(sf::RectangleShape(sf::Vector2f(rectangleSize, rectangleSize)));
		m_rectangles.at(i).setOutlineThickness(outlineThickness);
		m_rectangles.at(i).setOutlineColor(sf::Color::Red);
		m_rectangles.at(i).setFillColor(sf::Color::Transparent);
		m_rectangles.at(i).setPosition(sf::Vector2f(outlineThickness, windowHeight - (rectangleSize * (i + 1) + outlineThickness)));
	}

	for (int i = 0; i < m_destructibleMapElements.size(); i++)
	{
		spriteWidth = m_destructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().width;
		spriteHeight = m_destructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().height;
		//rectangles.at(i).setSize(sf::Vector2f(m_destructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().width, m_destructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().height));
		m_destructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(m_rectangles.at(i).getPosition().x, m_rectangles.at(i).getPosition().y));
		m_destructibleMapElements.at(i)->getSpritePtr()->setScale(sf::Vector2f(rectangleSize / spriteWidth, rectangleSize / spriteHeight));
	}
	for (int i = 0; i < m_indestructibleMapElements.size(); i++)
	{
		spriteWidth = m_indestructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().width;
		spriteHeight = m_indestructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().height;
		//rectangles.at(i + 1).setSize(sf::Vector2f(m_indestructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().width, m_indestructibleMapElements.at(i)->getSpritePtr()->getLocalBounds().height));
		m_indestructibleMapElements.at(i)->getSpritePtr()->setPosition(sf::Vector2f(m_rectangles.at(i + m_destructibleMapElements.size()).getPosition().x, m_rectangles.at(i + m_destructibleMapElements.size()).getPosition().y - outlineThickness));
		m_indestructibleMapElements.at(i)->getSpritePtr()->setScale(sf::Vector2f(rectangleSize / spriteWidth, rectangleSize / spriteHeight));
	}
}

void Editor::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	// Draw the remainder of the HUD
	window.draw(m_editorHUD);
	for (int i = 0; i < m_nrOfObjects; i++)
	{
		window.draw(m_rectangles.at(i));
	}
	for (int i = 0; i < m_destructibleMapElements.size(); i++)
		window.draw(*m_destructibleMapElements.at(i));
	for (int i = 0; i < m_indestructibleMapElements.size(); i++)
		window.draw(*m_indestructibleMapElements.at(i));
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

void Editor::update()
{

}
