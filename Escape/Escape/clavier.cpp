#pragma region includes
//includes sfml
#include <SFML/Graphics.hpp>
//includes c++
#include <stdio.h>
#include <stdlib.h>
#pragma endregion includes

void gestionClavier(sf::Event e, sf::Sprite sprite) {
	if (k.isKeyPressed(sf::Keyboard::Up)) {
		sprite.move(0, -1);
	}
}