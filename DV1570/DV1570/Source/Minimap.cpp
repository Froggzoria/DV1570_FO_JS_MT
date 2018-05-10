#include "..\Header\Minimap.h"


void Minimap::_init(sf::RenderTarget &window)
{
	float windowWidth = window.getSize().x;
	float windowHeight = window.getSize().y;
	float HUDHeight = windowHeight * 0.2f;
	int outlineThickness = 2.0f;

	// Create the minimap border
	m_minimapBorder = sf::RectangleShape(sf::Vector2f(HUDHeight, HUDHeight));
	m_minimapBorder.setFillColor(sf::Color::Transparent);
	m_minimapBorder.setOutlineThickness(outlineThickness);
	m_minimapBorder.setOutlineColor(sf::Color::Magenta);
	m_minimapBorder.setPosition(sf::Vector2f((windowWidth * 0.5f) - (HUDHeight * 0.5f), windowHeight - HUDHeight + outlineThickness));

	// Create the minimap
	float HUDAspectRatioWidth = HUDHeight / windowWidth;
	float HUDAspectRatioHeight = HUDHeight / windowHeight;
	m_minimapView.reset(sf::FloatRect(0.0f, 0.0f, windowWidth, windowHeight - HUDHeight));
	m_minimapView.setViewport(sf::FloatRect((0.5f - (HUDAspectRatioWidth * 0.5)), (1.0f - HUDAspectRatioHeight), HUDAspectRatioWidth, HUDAspectRatioHeight));
}

void Minimap::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	// Render to minimap here
	window.setView(m_minimapView);

	window.setView(window.getDefaultView());
	
	// Render remaining minimap elements
	window.draw(m_minimapBorder);
}

Minimap::Minimap(sf::RenderTarget &window)
{
	_init(window);
}

Minimap::~Minimap()
{
}

void Minimap::update()
{
}
