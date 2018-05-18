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
}

Weapon::~Weapon()
{

}

void Weapon::shoot(float dt)
{
	//funderar på luftmotstånd här
}

void Weapon::setValues()
{
	float tempVelocity = 45.0f;
	float tempAngle = 45.0f;
	this->velocityX = tempVelocity * cos(tempAngle * PI / 180);
	this->velocityY = tempVelocity * sin(tempAngle * PI / 180);

	this->velocityVector.x = this->velocityX;
	this->velocityVector.y = this->velocityY;
	this->normalize();
}

void Weapon::update(float dt, sf::Vector2f pos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->shape.setPosition(pos);
		this->setValues();

	}
	this->velocity = sqrt(pow(this->velocityX, 2) + pow(this->velocityY, 2));
	this->shoot(dt);
	this->shape.move(this->velocityX * dt, -this->velocityY * dt);
}

void Weapon::draw(sf::RenderTarget & target, sf::RenderStates & states) const
{
	target.draw(this->shape, states);
}
