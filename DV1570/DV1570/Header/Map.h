#pragma once
#include "Object.h"

class Map : public sf::Drawable
{
private:

	void _init();

	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

public:
	Map();
	virtual~Map();

};