#ifndef PLAYER_H
#define PLAYER_H

#include<SFML\Graphics.hpp>

class Player : public sf::Drawable
{
private:

public:
	Player();
	~Player();

	void update(float dt);
};
#endif
