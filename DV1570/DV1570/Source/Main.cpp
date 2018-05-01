#include "../Header/GameState.h"
#include "../Header/MainMenuState.h"

int main()
{
	std::stack<State*> gameStates;
	GameState* test;

	gameStates.push(dynamic_cast<State*>(test));
	//gameStates.top()->draw();

	return 0;
}