#pragma region includes
//includes sfml
#include <SFML/Graphics.hpp>
//includes c++
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#pragma endregion includes

#pragma region variables
//variables d'écran
int xScreen = GetSystemMetrics(SM_CXFULLSCREEN);
int yScreen = GetSystemMetrics(SM_CYFULLSCREEN);

//variables de texture
sf::Texture hero;
sf::Sprite sprite_hero;
#pragma endregion variables

int main(){

	//ouverture de la fenetre
	sf::RenderWindow window(sf::VideoMode(xScreen, yScreen-10), "Escape", sf::Style::Default);
	window.setPosition(sf::Vector2i(-10, 0));

	//affichage des sprites
	if (!hero.loadFromFile("hero.png", sf::IntRect(0,0,32,32))) {
		std::cout << "Erreur de chargement des sprites" << std::endl;
	}
	hero.setSmooth(true);
	sprite_hero.setTexture(hero);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(sprite_hero);
		window.display();
		window.clear();
		
	}

	return 0;
}