#include "../Header/GameState.h"
#include "../Header/MainMenuState.h"

int main()
{
	std::stack<State*> gameStates;
	
	GameState* test = new GameState();

	gameStates.push(test);


	return 0;
}