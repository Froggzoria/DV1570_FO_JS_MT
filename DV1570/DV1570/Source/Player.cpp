#include "Player.h"

sf::Vector2f Player::getCenterPos() const
{
	sf::Vector2f pos = sprite.getPosition();
	sf::IntRect bounds = sprite.getTextureRect();
	pos.x = pos.x + bounds.width / 2;
	pos.y = pos.y + bounds.height / 2;
	return pos;
}

void Player::draw(lua_State * L, sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	wep.draw(L, target, states);
	if (drawConvexShape)
		target.draw(this->coneShape, states);
		
}

Player::Player(const char* name, unsigned int hp, sf::Vector2f pos)
{
	this->name = name;
	this->hp = hp;
	sf::String fileName = "..//Resources//player1.png";
	if (!texture.loadFromFile(fileName))
	{
		// Handle error: Print error message.
		std::cout << "ERROR: Player image could not be loaded.\n---" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	// Initialize animation variables.
	currentKeyFrame = sf::Vector2i(0, 0);
	keyFrameSize = sf::Vector2i(32, 32);
	spriteWidth = 4;
	animationSpeed = 0.2f;
	keyFrameDuration = 0.0f;
	sprite.setPosition(pos);
}

Player::~Player()
{

}

void Player::update(float dt, lua_State * L, const sf::Window &win)
{
	if (luaL_dofile(L, "Scripts//Player.lua") != EXIT_SUCCESS)
		printf(*lua_tostring(L, -1)+"\n");

	this->OnMove(L);
	if (!this->wep.hasProjectile)
		this->OnShoot(L, win);
	this->OnJump(L);
	//Update animation
	if (keyFrameDuration >= animationSpeed)
	{
		currentKeyFrame.x++;

		if (currentKeyFrame.x >= spriteWidth)
			currentKeyFrame.x = 0;

		sprite.setTextureRect(sf::IntRect(currentKeyFrame.x * keyFrameSize.x,
			currentKeyFrame.y * keyFrameSize.y, keyFrameSize.x, keyFrameSize.y));
		keyFrameDuration = 0.0f;
	}
	this->wep.Update(L);
}

void Player::calculateConvexShape(double multiplier, const sf::Window &win)
{
	static const int nrOfConePoints = 4;
	static const float scalingValue = 12.0;
	if (multiplier > MAX_SPEED_MULTIPLIER)
		multiplier = MAX_SPEED_MULTIPLIER;
	sf::Vector2i cursorPos = sf::Mouse::getPosition(win);
	sf::Vector2f playerPos = this->getCenterPos();
	sf::Vector2f direction = sf::Vector2f(cursorPos.x - playerPos.x, cursorPos.y - playerPos.y);
	float length = sqrt(direction.x*direction.x + direction.y*direction.y);
	direction.x = (direction.x / length) * scalingValue * multiplier;
	direction.y = (direction.y / length) * scalingValue * multiplier;
	this->coneShape.setPointCount(nrOfConePoints);
	this->coneShape.setPoint(0, playerPos);
	sf::Vector2f tempDir;

	tempDir.x = cos(angle)*direction.x - sin(angle)*direction.y;
	tempDir.y = sin(angle)*direction.x + cos(angle)*direction.y;
	coneShape.setPoint(1, playerPos + tempDir);
	coneShape.setPoint(2, playerPos + direction);
	tempDir.x = cos(-angle)*direction.x - sin(-angle)*direction.y;
	tempDir.y = sin(-angle)*direction.x + cos(-angle)*direction.y;
	coneShape.setPoint(3, playerPos + tempDir);

	sf::Color color((2 / 3 * 255 + 1 / multiplier * 255), 0, 0);
	this->coneShape.setFillColor(color);
}

void Player::OnMove(lua_State * L)
{
	//only run the script on input
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
		lua_setglobal(L, "MOVE_LEFT");
		lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
		lua_setglobal(L, "MOVE_RIGHT");
		lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
		lua_setglobal(L, "MOVE_UP");
		lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
		lua_setglobal(L, "MOVE_DOWN");

		lua_getglobal(L, "MovePlayer");
		lua_pushlightuserdata(L, (void*)this);
		//ALWYAS SET THE METATABLE WE ARE GOING TO NEED BEFORE RUNNING THE SCRIPT
		luaL_setmetatable(L, LUA_PLAYER);
		if (lua_pcall(L, 1, 0, 0) != EXIT_SUCCESS)
		{
			printf((*lua_tostring(L, -1)+"\n"));
		}
	}
}

void Player::OnShoot(lua_State * L, const sf::Window &win)
{
	static bool fireKeyPressed = false;
	static double projectile_multiplier = MIN_SPEED_MULTIPLIER;
	double dt = m_timer.restart().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		fireKeyPressed = true;
		projectile_multiplier += dt;
		calculateConvexShape(projectile_multiplier, win);
		drawConvexShape = true;
	}
		

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F) && fireKeyPressed)
	{
		fireKeyPressed = false;
		drawConvexShape = false;
		if (projectile_multiplier > MAX_SPEED_MULTIPLIER)
			projectile_multiplier = MAX_SPEED_MULTIPLIER;

		lua_pushnumber(L, (projectile_multiplier*PROJECTILE_SPEED_CONSTANT));
		lua_setglobal(L, "PROJECTILE_SPEED");
		projectile_multiplier = MIN_SPEED_MULTIPLIER;

		lua_getglobal(L, "OnShoot");
		lua_pushlightuserdata(L, (void*)this);
		//ALWYAS SET THE METATABLE WE ARE GOING TO NEED BEFORE RUNNING THE SCRIPT
		luaL_setmetatable(L, LUA_PLAYER);
		sf::Vector2i cursorPos = sf::Mouse::getPosition(win);
		lua_pushnumber(L, cursorPos.x);
		lua_pushnumber(L, cursorPos.y);
		if (lua_pcall(L, 3, 1, 0) != EXIT_SUCCESS)
		{
			printf(lua_tostring(L, -1));
			printf("\n");
		}
		else
		{
			Projectile *p = (Projectile *)lua_touserdata(L, -1);
			this->wep.setNewProjectilePtr(p, this->getCenterPos());
			lua_pop(L, 1);
			if (luaL_dofile(L, "Scripts//Projectile.lua") != EXIT_SUCCESS)
				printf(lua_tostring(L, -1));
			else
			{
				lua_getglobal(L, "RunUpdateThread");
				lua_pushlightuserdata(L, (void*)p);
				luaL_setmetatable(L, LUA_PROJECTILE);
				if (lua_pcall(L, 1, 0, 0) != EXIT_SUCCESS)
				{
					printf(lua_tostring(L, -1));
					printf("\n");
				}
			}

		}

	}
}

void Player::OnJump(lua_State * L)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_isTouchingGround)
	{
		m_isTouchingGround = false;
		lua_getglobal(L, "CreateJumpThread");
		lua_pushlightuserdata(L, (void*)this);
		luaL_setmetatable(L, LUA_PLAYER);
		if (lua_pcall(L, 1, 0, 0) != EXIT_SUCCESS)
		{
			printf(lua_tostring(L, -1));
			printf("\n");
		}
	}
	if (!m_isTouchingGround)
	{
		
		lua_getglobal(L, "ResumeJumpThread");
		lua_pushlightuserdata(L, (void*)this);
		luaL_setmetatable(L, LUA_PLAYER);
		if (lua_pcall(L, 1, 0, 0) != EXIT_SUCCESS)
		{
			printf(lua_tostring(L, -1));
			printf("\n");
		}
		
		sf::Vector2f pos = this->getCenterPos();
		if (pos.y > 500)
			m_isTouchingGround = true;

	}
}
