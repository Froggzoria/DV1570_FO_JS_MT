#include "../Header/GameState.h"
#include "../Header/MainMenuState.h"
#include "../Header/Editor.h"
#include "../Header/Minimap.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(800, 600), "Frogge Test");
	std::stack<State*> gameStates;
	
	GameState* test = new GameState("");
	gameStates.push(test);

	Editor editor(window);
	Minimap minimap(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		editor.update(window);
		window.clear(sf::Color::Black);
		window.draw(editor);
		window.draw(minimap);
		window.display();
	}

	delete test;

	return 0;
}