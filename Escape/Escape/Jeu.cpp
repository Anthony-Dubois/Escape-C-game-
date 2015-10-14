#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdio.h>

int main(){
	
	
	int xScreen = GetSystemMetrics(SM_CXFULLSCREEN);
	int yScreen = GetSystemMetrics(SM_CYFULLSCREEN);
	sf::RenderWindow window(sf::VideoMode(xScreen, yScreen-10), "Escape", sf::Style::Default);
	window.setPosition(sf::Vector2i(-10, 0));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}