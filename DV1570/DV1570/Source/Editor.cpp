#include "Editor.h"

void Editor::_init()
{
	this->m_buildMode = false;
	// Initialize the different map tiles and objects
	Object nextMapElement;
	std::string pathToTexture = "";
	//sf::IntRect area;
	//sf::Vector2f pos;
	nextMapElement = Object(pathToTexture);
	this->m_mapElements.push_back(nextMapElement);
}

Editor::Editor()
{
	this->_init();
}

Editor::~Editor()
{

}

void Editor::enterBuildMode()
{
	this->m_buildMode = true;
}

void Editor::exitBuildMode()
{
	this->m_buildMode = false;
	// Open file stream to save the map

}

bool Editor::getIndestructibleElements() const
{
	return false;
}

void Editor::setIndestructibleElements(bool indestructible)
{
}

void Editor::draw() const
{
}

void Editor::update()
{
}
