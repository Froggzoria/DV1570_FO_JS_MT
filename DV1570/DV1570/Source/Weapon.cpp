#include"weapon.h"

Weapon::Weapon()
{
	sf::String filepath = "..//Resources//grenade.png";
	if (!this->m_texture.loadFromFile(filepath))
		printf("Unable to load grenade texture\n");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	m_sprite.setOrigin(16.f, 16.f);
}

Weapon::~Weapon()
{

}



void Weapon::draw(lua_State *L, sf::RenderTarget & target, sf::RenderStates states) const
{
	if (currentProjectile)
		currentProjectile->Render(L, target, states);
}

void Weapon::Update(lua_State *L)
{

	lua_getglobal(L, "REMOVE_PROJECTILE");
	if (lua_toboolean(L, 1))
	{
		hasProjectile = false;
		this->currentProjectile = nullptr;
		lua_pushboolean(L, false);
		lua_setglobal(L, "REMOVE_PROJECTILE");
	}
}


void Projectile::Render(lua_State *L, sf::RenderTarget & target, sf::RenderStates states) const
{
	if (luaL_dofile(L, "Scripts//Projectile.lua") != EXIT_SUCCESS)
		printf(lua_tostring(L, -1));
	else
	{
		target.draw(*this->body, states);
		//resume thread
		lua_getglobal(L, "ResumeUpdate");
		lua_pushlightuserdata(L, (void*)this);
		luaL_setmetatable(L, LUA_PROJECTILE);
		if (lua_pcall(L, 1, 0, 0) != EXIT_SUCCESS)
		{
			printf(lua_tostring(L, -1));
			printf("\n");
		}
	}
}

sf::Vector3f Projectile::getCenterPosAndRadius() const
{
	sf::Vector2f pos = this->body->getPosition();
	sf::IntRect bounds = this->body->getTextureRect();
	pos.x += bounds.width / 2;
	pos.y += bounds.height / 2;
	float radius = bounds.width / 2;
	return sf::Vector3f(pos.x, pos.y, radius);
}
