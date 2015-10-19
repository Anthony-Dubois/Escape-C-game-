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
#include "Particules.cpp"
#include "Hero.cpp"
#include "TileMap.cpp"
#pragma endregion includes

#pragma region variables
//variables d'écran
int xScreen = GetSystemMetrics(SM_CXFULLSCREEN);
int yScreen = GetSystemMetrics(SM_CYFULLSCREEN) - 10;

//variables de texture
sf::Texture hero;
sf::Sprite sprite_hero;

//Variables de gestion du jeu
sf::Vector2i positionSouris;
int speed = 1;
enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
int blockSize = 32;
bool updateFPS = true;
#define RAND_MAX = 1;
bool pause = true;

//variables de vue
sf::View view;
#pragma endregion variables

 
#pragma region prototypes
void clavier();
void souris();
void animation();
void vue();
#pragma endregion prototypes

int main() {

	//ouverture de la fenêtre
	sf::RenderWindow window(sf::VideoMode(xScreen, yScreen), "Escape", sf::Style::Default);
	window.setPosition(sf::Vector2i(-10, 0));

	sf::Clock clock;
	ParticleSystem particles(10000);

	//affichage des sprites
	if (!hero.loadFromFile("hero.png"))
		std::cout << "Erreur de chargement des sprites" << std::endl;
	hero.setSmooth(true);
	sprite_hero.setTexture(hero);


	int level[3200];
	for (int i = 0; i < 3200; i++) {
		int nb = std::rand() % 100;
		std::cout << nb << std::endl;
		if (nb < 5) {
			level[i] = 0;
		}
		else if (nb < 10) {
			level[i] = 1;
		}
		else if (nb < 25) {
			level[i] = 2;
		}
		else
			level[i] = 3;
	}


	// on crée la tilemap avec le niveau précédemment défini
	TileMap map;
	if (!map.load("tileset.gif", sf::Vector2u(32, 32), level, 80, 40))
		return -1;



	//Tant que la fenêtre est ouverte
	while (window.isOpen()){
		sf::Event event;



		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				updateFPS = true;
			}else
				updateFPS = false;
		}

		/*Gestion des évènements*/
		clavier();
		souris();
		animation();
		vue();

		



		/*Gestion des particules*/
		sf::Vector2i perso(sprite_hero.getPosition().x+ blockSize/2,sprite_hero.getPosition().y+ blockSize/2);
		sf::Vector2i milieuX(xScreen / 2, sprite_hero.getPosition().y + blockSize / 2);
		sf::Vector2i milieuY(sprite_hero.getPosition().x + blockSize / 2, yScreen / 2);
		sf::Vector2i milieu(xScreen / 2, yScreen / 2);
		if(sprite_hero.getPosition().x+blockSize/2 < xScreen/2 && sprite_hero.getPosition().y + blockSize / 2 < yScreen / 2) {
			particles.setEmitter(window.mapPixelToCoords(perso));
		}
		else if (sprite_hero.getPosition().x + blockSize / 2 > xScreen / 2 && sprite_hero.getPosition().y + blockSize / 2 > yScreen / 2) {
			particles.setEmitter(window.mapPixelToCoords(milieu));
		}
		else if (sprite_hero.getPosition().x + blockSize / 2 < xScreen /2) {
			particles.setEmitter(window.mapPixelToCoords(milieuY));
		}
		else if (sprite_hero.getPosition().y + blockSize / 2 < yScreen /2) {
			particles.setEmitter(window.mapPixelToCoords(milieuX));
		}



		sf::Time elapsed = clock.restart();
		particles.update(elapsed);


		window.setView(view);
		
		window.clear();
		window.draw(map);
		window.draw(particles);
		window.draw(sprite_hero);
		window.display();
		
		
	}

	return 0;
}


//gestion du clavier
void clavier() {
	if (!pause) {
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

		if (sprite_hero.getPosition().x <= 0)
			sprite_hero.setPosition(sf::Vector2f(0, sprite_hero.getPosition().y));
		if (sprite_hero.getPosition().y <= 0)
			sprite_hero.setPosition(sf::Vector2f(sprite_hero.getPosition().x, 0));
		if (sprite_hero.getPosition().x >= 79 * blockSize)
			sprite_hero.setPosition(sf::Vector2f(79 * blockSize, sprite_hero.getPosition().y));
		if (sprite_hero.getPosition().y >= 39 * blockSize)
			sprite_hero.setPosition(sf::Vector2f(sprite_hero.getPosition().x, 39 * blockSize));
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
		if (time.getElapsedTime().asMilliseconds() >= 20) {
			anim.x++;
			if ((anim.x * blockSize) >= hero.getSize().x)
				anim.x = 0;
			time.restart();
		}
	}
	sprite_hero.setTextureRect(sf::IntRect(anim.x * blockSize, anim.y * blockSize, blockSize, blockSize));
}

//gestion de la vue
void vue() {
	/* création d'une vue de la taille de l'écran
	avec le héro au milieu de l'écran */
	view.reset(sf::FloatRect(0, 0, xScreen, yScreen));
	sf::Vector2f position(xScreen / 2, yScreen / 2);
	position.x = sprite_hero.getPosition().x + (blockSize / 2) - (xScreen / 2);
	position.y = sprite_hero.getPosition().y + (blockSize / 2) - (yScreen / 2);

	if (position.x < 0)
		position.x = 0;
	if (position.y < 0)
		position.y = 0;
	view.reset(sf::FloatRect(position.x, position.y, xScreen, yScreen));
	//view.zoom(0.2f);
}