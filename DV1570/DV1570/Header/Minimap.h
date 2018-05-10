#pragma once
#include "Object.h"

class Minimap : public sf::Drawable
{
private:
	sf::View m_minimapView;
	sf::RectangleShape m_minimapBorder;

	void _init(sf::RenderTarget &window);

	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

public:
	Minimap(sf::RenderTarget &window);
	virtual ~Minimap();

	void update();
};