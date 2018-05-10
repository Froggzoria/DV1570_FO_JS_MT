#include "../Header/GameState.h"
#include "../Header/MainMenuState.h"
#include "../Header/Editor.h"
#include "../Header/Minimap.h"

int main()
{
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

		window.clear(sf::Color::Black);
		window.draw(editor);
		window.draw(minimap);
		window.display();
	}


	return 0;
}