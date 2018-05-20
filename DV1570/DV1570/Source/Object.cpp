#include <Object.h>

Object::Object()
{
}

Object::Object(std::string pathToTexture, sf::IntRect area, sf::Vector2f position)
{
	if (m_texture.loadFromFile(pathToTexture, area))
	{
		m_pos = position;
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(m_pos);
	}
	else
		throw std::invalid_argument("Texture could not be loaded. Bad Path");
}

Object::Object(const Object& other)
{
	m_pos = other.m_pos;
	m_texture = other.m_texture;
	m_sprite.setTexture(m_texture);
}

Object::~Object()
{
}

sf::Sprite* Object::getSpritePtr()
{
	return &this->m_sprite;
}

void Object::update()
{
	m_sprite.setPosition(m_pos);
}

void Object::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(m_sprite, states);
}

