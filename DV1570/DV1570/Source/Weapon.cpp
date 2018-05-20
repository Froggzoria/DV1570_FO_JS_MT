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
<<<<<<< HEAD
<<<<<<< HEAD
	//this is all very temp

	sf::Vector2f dirVec = sf::Vector2f(sf::Mouse::getPosition(win).x - pos.x, sf::Mouse::getPosition(win).y - pos.y);
	float lengthSquare = (dirVec.x * dirVec.x) + (dirVec.y * dirVec.y);
	dirVec.x = (dirVec.x * dirVec.x) / lengthSquare;
	float rotAngle = acos(dirVec.x) *(180 / PI);
=======
	////this is all very temp
	//sf::Vector2f dirVec = sf::Vector2f(sf::Mouse::getPosition(win).x - pos.x, sf::Mouse::getPosition(win).y - pos.y);
	//float lengthSquare = (dirVec.x * dirVec.x) + (dirVec.y * dirVec.y);
	//dirVec.x = (dirVec.x * dirVec.x) / lengthSquare;
	//float rotAngle = acos(dirVec.x) *(180 / PI);
>>>>>>> Jakob

	//float tempVelocity = 150.0f;
	////float tempAngle = 45.0f;
	//this->massKG = 2.0f;

	//this->velocityX = tempVelocity * cos(rotAngle *PI / 180);
	//this->velocityY = tempVelocity * sin(rotAngle *PI / 180);

	//this->velocityVector.x = this->velocityX;
	//this->velocityVector.y = this->velocityY;
	//this->normalize();

	//this->k = 0.5f * (1.293f * PI * std::pow((this->shape.getRadius() / 100), 2)) / (2 * this->massKG);
=======
	lua_getglobal(L, "REMOVE_PROJECTILE");
	if (lua_toboolean(L, 1))
	{
		hasProjectile = false;
		this->currentProjectile = nullptr;
		lua_pushboolean(L, false);
		lua_setglobal(L, "REMOVE_PROJECTILE");
	}
>>>>>>> Jakob
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
<<<<<<< HEAD
	this->velocity = sqrt(pow(this->velocityX, 2) + pow(this->velocityY, 2));
	this->shoot(dt);
<<<<<<< HEAD
	this->shape.move(this->velocityX * dt, -this->velocityY * dt);

=======
>>>>>>> Jakob
=======
>>>>>>> Jakob
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
