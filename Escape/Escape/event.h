#pragma region includes
//includes sfml
#include <SFML/Graphics.hpp>
#pragma endregion includes

#pragma region variables
//Variables de gestion du jeu
int speed = 1;
#pragma endregion variables

//gestion du clavier
void clavier(sf::Sprite sprite) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		sprite.move(0, -speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		sprite.move(0, speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		sprite.move(-speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		sprite.move(speed, 0);
	}
}

//gestion de la souris
void souris(sf::Sprite sprite) {

}