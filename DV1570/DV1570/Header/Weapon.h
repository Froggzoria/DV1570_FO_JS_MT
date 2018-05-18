#ifndef WEAPON_H
#define WEAPON_H
#include<SFML\Graphics.hpp>
#include<math.h>
using namespace std;

static const float GRAVITY = 9.82f;
static const float PI = 3.14f;
class Weapon
{
private:
	sf::Vector2f pos;
	sf::CircleShape shape;

	float velocity;
	float velocityX;
	float velocityY;
	sf::Vector2f velocityVector;
	sf::Vector2f normalizedVector;

	void normalize();

	string name;
public:
	Weapon();
	~Weapon();

	void shoot(float dt);
	void setValues();
	void update(float dt, sf::Vector2f pos);

	void draw(sf::RenderTarget &target, sf::RenderStates &states) const;
};
#endif // !WEAPON_H

