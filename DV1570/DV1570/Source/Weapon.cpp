#include"weapon.h"

void Weapon::normalize()
{
	float magnitude = sqrt((this->velocityVector.x * this->velocityVector.x) + (this->velocityVector.y * this->velocityVector.y));
	this->normalizedVector.y = this->velocityVector.y / magnitude;
	this->normalizedVector.x = this->velocityVector.x / magnitude;
}

Weapon::Weapon()
{
	this->name = "?";
	this->shape = sf::CircleShape(5.0f);
	this->shape.setFillColor(sf::Color::Red);
	this->velocity = 0.0f;
	this->velocityX = 0.0f;
	this->velocityY = 0.0f;
	this->k = 0.0f;
	this->massKG = 0.0f;
}

Weapon::~Weapon()
{

}

void Weapon::shoot(float dt)
{
	//just some physics
	float force = -this->k * this->velocity * this->velocity;

	float a = force / this->massKG;
	float retardationX = a * -this->normalizedVector.x;
	float retardationY = a * -this->normalizedVector.y + GRAVITY;

	this->velocityX -= retardationX * dt;
	this->velocityY -= retardationY * dt;

	this->velocityVector.x = this->velocityX;
	this->velocityVector.y = this->velocityY;
	this->normalize();

}

void Weapon::setValues(const sf::Window &win, sf::Vector2f pos)
{
	//this is all very temp
	sf::Vector2f dirVec = sf::Vector2f(sf::Mouse::getPosition(win).x - pos.x, sf::Mouse::getPosition(win).y - pos.y);
	float lengthSquare = (dirVec.x * dirVec.x) + (dirVec.y * dirVec.y);
	dirVec.x = (dirVec.x * dirVec.x) / lengthSquare;
	float rotAngle = acos(dirVec.x) *(180 / PI);

	float tempVelocity = 150.0f;
	//float tempAngle = 45.0f;
	this->massKG = 2.0f;

	this->velocityX = tempVelocity * cos(rotAngle *PI / 180);
	this->velocityY = tempVelocity * sin(rotAngle *PI / 180);

	this->velocityVector.x = this->velocityX;
	this->velocityVector.y = this->velocityY;
	this->normalize();

	this->k = 0.5f * (1.293f * PI * std::pow((this->shape.getRadius() / 100), 2)) / (2 * this->massKG);
}

void Weapon::update(float dt, sf::Vector2f pos, const sf::Window &win)
{
	//this function is mostly done i think
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->shape.setPosition(pos);
		this->setValues(win, pos);

	}
	this->velocity = sqrt(pow(this->velocityX, 2) + pow(this->velocityY, 2));
	this->shoot(dt);
	this->shape.move(this->velocityX * dt, -this->velocityY * dt);
}

void Weapon::draw(sf::RenderTarget & target, sf::RenderStates & states) const
{
	target.draw(this->shape, states);
}
