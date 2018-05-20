#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML\Graphics.hpp>
#include"Player.h"
#include "SpawnPoint.h"
#include "GameTile.h"
#include <vector>

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class Game : public sf::Drawable
{
private:
	sf::Texture backgroundTex;
	sf::Sprite backgroundSprite;
	std::vector<Player*> players;
	std::vector<SpawnPoint*> spawnPoints;
	std::vector<GameTile*> gameTiles;
	lua_State * L;

	// Player turn tracker
	int m_playerTurn;
	float m_turnTime;
	float m_turnLimit;
	sf::Font m_font;
	sf::Text m_playerTurnText;
	sf::Text m_turnTimeText;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void getPlayersFromLua(lua_State * L);
	void getSpawnPointsFromLua(lua_State* L);
	void getGameTilesFromLua(lua_State* L);
public:
	Game();

	bool init(lua_State * L);

	void Update(float dt, const sf::Window &win, lua_State *L);
};
#endif