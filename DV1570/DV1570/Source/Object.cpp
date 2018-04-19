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


Object::~Object()
{
}

sf::Sprite * Object::getSpritePtr()
{
	return &this->m_sprite;
}

void Object::update()
{
	m_sprite.setPosition(m_pos);
}

