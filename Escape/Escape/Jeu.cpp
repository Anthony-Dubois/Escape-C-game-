#pragma region includes
//includes sfml
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
//includes c++
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//classes externes

#pragma endregion includes

#pragma region variables
//variables d'écran
int xScreen = GetSystemMetrics(SM_CXFULLSCREEN);
int yScreen = GetSystemMetrics(SM_CYFULLSCREEN);

//variables de texture
sf::Texture hero;
sf::Sprite sprite_hero;

//Variables de gestion du jeu
sf::Vector2i positionSouris;
int speed = 1;
enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
int blockSize = 32;
bool updateFPS = false;
#pragma endregion variables

 
#pragma region prototypes
void clavier();
void souris();
void animation();
#pragma endregion prototypes
int main() {

	//ouverture de la fenêtre
	sf::RenderWindow window(sf::VideoMode(xScreen, yScreen - 10), "Escape", sf::Style::Default);
	window.setPosition(sf::Vector2i(-10, 0));
	
	//affichage des sprites
	if (!hero.loadFromFile("hero.png"))
		std::cout << "Erreur de chargement des sprites" << std::endl;
	hero.setSmooth(true);
	sprite_hero.setTexture(hero);


	//Tant que la fenêtre est ouverte
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				updateFPS = true;
			}
			else
				updateFPS = false;
		}

		/*Gestion des évènements*/
		clavier();
		souris();
		animation();
		

		window.draw(sprite_hero);
		window.display();
		window.clear();
		
	}

	return 0;
}


//gestion du clavier
void clavier() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		anim.y = Up;
		sprite_hero.move(0, -speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		anim.y = Down;
		sprite_hero.move(0, speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		anim.y = Left;
		sprite_hero.move(-speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		anim.y = Right;
		sprite_hero.move(speed, 0);
	}
}

//gestion de la souris
void souris() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		/*
			positionSouris = sf::Mouse::getPosition(window);
			std::cout << "Mouse.x" << positionSouris.x << "Mouse.y" << positionSouris.y << std::endl;
		*/
	}
}

//gestion de l'animation
void animation() {
	sf::Clock time;
	if (updateFPS == true){
		if (time.getElapsedTime().asMilliseconds() >= 50) {
			anim.x--;
			if ((anim.x * blockSize) >= hero.getSize().x)
				anim.x = 1;
			time.restart();
		}
	}
	sprite_hero.setTextureRect(sf::IntRect(anim.x * blockSize, anim.y * blockSize, blockSize, blockSize));
}