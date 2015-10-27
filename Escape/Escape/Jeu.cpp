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
bool menu = true;

//variables de vue
sf::View view;
#pragma endregion variables
sf::Font font;

 
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
	if (!map.load("tileset.gif", sf::Vector2u(64, 64), level, 80, 40))
		return -1;



	/*Menu de début*/
	if (!font.loadFromFile("Northwood High.ttf"))
		std::cout << "Erreur de chargement du menu" << std::endl;
	sf::Text text;
	text.setFont(font);
	text.setString("Escape !");
	text.setCharacterSize(120);
	text.setColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(xScreen/2 -400, yScreen / 6));

	if (!font.loadFromFile("DK_Crayon_Crumble.ttf"))
		std::cout << "Erreur de chargement du menu" << std::endl;
	sf::Text text2;
	text2.setFont(font);
	text2.setString("Echape toi de ce niveau !");
	text2.setCharacterSize(50);
	text2.setColor(sf::Color::White);
	text2.setPosition(sf::Vector2f(xScreen / 2 - 400, yScreen / 5 + 150));

	sf::Text text3;
	text3.setFont(font);
	text3.setString("Attention le sol n'en fait qu'à sa tête !");
	text3.setCharacterSize(50);
	text3.setColor(sf::Color::White);
	text3.setPosition(sf::Vector2f(xScreen / 2 - 400, yScreen / 5 +210));
	
	sf::Text text4;
	text4.setFont(font);
	text4.setString("Utilise les flèches pour te déplacer et espace pour attaquer.");
	text4.setCharacterSize(50);
	text4.setColor(sf::Color::White);
	text4.setPosition(sf::Vector2f(xScreen / 2 - 400, yScreen / 5+270));

	sf::Text text5;
	text5.setFont(font);
	text5.setString("appuie sur entrée pour commencer !");
	text5.setCharacterSize(50);
	text5.setColor(sf::Color::Red);
	text5.setPosition(sf::Vector2f(xScreen / 2 - 400, yScreen / 5+360));
		
	/*
	if (!font.loadFromFile("DK_Crayon_Crumble.ttf"))
		std::cout << "Erreur de chargement du menu" << std::endl;
	sf::Text score;
	score.setFont(font);
	score.setString("Score :");
	score.setCharacterSize(50);
	score.setColor(sf::Color::Red);
	score.setPosition(sf::Vector2f(xScreen / 8 - 200, yScreen -80 ));
	*/



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
		if (!menu) {
			window.draw(particles);
		}
		window.draw(sprite_hero);
		if (menu) {
			window.draw(text);
			window.draw(text2);
			window.draw(text3);
			window.draw(text4);
			window.draw(text5);
		}
		

		window.display();
		
		
	}

	return 0;
}


//gestion du clavier
void clavier() {
	if (!menu) {
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
		if (sprite_hero.getPosition().x >= 79 * blockSize*2+32)
			sprite_hero.setPosition(sf::Vector2f(79 * blockSize*2+32, sprite_hero.getPosition().y));
		if (sprite_hero.getPosition().y >= 39 * blockSize*2+32)
			sprite_hero.setPosition(sf::Vector2f(sprite_hero.getPosition().x, 39 * blockSize*2+32));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		menu = false;
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