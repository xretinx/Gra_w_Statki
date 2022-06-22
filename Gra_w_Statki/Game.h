#pragma once
#include "Statki.h"
#include "Plansze.h"
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
class Game
{
public:
	//Obiekt window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	//Obiekt event
	sf::Event ev;

	//Pozycja myszy
	sf::Vector2i mousePos;
	sf::Vector2i mousePosReference;

	//Przycisk enter
	bool isEnterPressed;

	//Obiekty Gry
	int shipSizes[10]; 
	int shipNumber=-1;
	static bool isShipSet;
	std::vector <Statki> ships;
	static int board1[10][10];
	static int board2[10][10];
	Plansze boards;

	int round = 0;
	int pos = 0;
	int tiles[100];
	int wynik{};
	int polaspudlowane{};
	int polatrafione{};
	void bot();

	//do menu i nwm co z tym zrobic
	sf::RectangleShape menu;
	sf::RectangleShape button1;
	sf::RectangleShape button2;
	sf::RectangleShape button3;
	sf::RectangleShape buttons[3] = { button1, button2, button3 };

	sf::Font font;
	sf::Text score;
	sf::Text button1text;
	sf::Text button2text;
	sf::Text button3text;
	sf::Text buttonsText[3] = { button1text, button2text, button3text };

	bool mainMenu = 1;
	bool stopMenu = 1;
	bool stop = 1;
	int temp = 0;
	int shipcount = 0;

	int prevKey = sf::Keyboard::Escape;

	void initFont();
	void initText();
	void pauseMenu();

	//--------------------

	//T³a
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::RectangleShape background2;
	sf::Texture backgroundTexture2;
	sf::RectangleShape background3;
	sf::Texture backgroundTexture3;

	//Czy przesuwamy obiekt

	//Funkcje prywatne, wywo³ywane raz na pocz¹tku gry
	void initializerVariables();
	void initWindow();
	void initShip();
	void initBackground();
	void initMenu();
	void initScore();

public:
	//Konstruktory
	Game();
	~Game();

	//Akcesoria
	bool running();
	int winning();
	void gameReset();

	//Funkcje
	void pollEvents();
	bool isInside(sf::Vector2i mouse, sf::FloatRect rect);
	void updateMousePosition();
	void updateShipPosition();
	void updateScore();

	void update();
	
	void renderShip();
	void renderBackground();
	void renderScore();
	void render();
};

